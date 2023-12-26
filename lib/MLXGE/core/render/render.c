/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 09:20:53 by lmells            #+#    #+#             */
/*   Updated: 2023/12/26 13:18:21 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <render.h>

static inline t_image	*clear_layer_frame(t_image *frame,
								bool is_mlx_object)
{
	void	*mlx_instance;

	if (is_mlx_object)
	{
		mlx_instance = get_core()->mlx_inst_ptr;
		if (frame->mlx_ptr)
			mlx_destroy_image(mlx_instance, frame->mlx_ptr);
		frame->mlx_ptr = mlx_new_image(mlx_instance, frame->size.width,
				frame->size.height);
		frame->buff = (int *)mlx_get_data_addr(frame->mlx_ptr,
				&frame->ctx[0], &frame->ctx[1], &frame->ctx[2]);
	}
	mlxge_fill(frame, frame->bg_colour);
	return (frame);
}

inline void	draw_layer_frame(t_zbuff_tree *z_buffer, t_image *layer_frame)
{
	int				i;
	t_zbuff_node	*leaf;
	t_image			*image;

	i = -1;
	while (++i < z_buffer->z_range)
	{
		leaf = z_buffer->branches[i];
		while (leaf)
		{
			image = *leaf->image_ref;
			layer_frame = set_pixels(layer_frame, image, image->origin);
			leaf = leaf->next;
		}
	}
}

static inline void	update_layer_viewports(t_viewport *viewports)
{
	t_v2d			project;
	t_image			*image;
	t_cam_ortho2d	cam;

	while (viewports)
	{
		viewports->frame = clear_layer_frame(viewports->frame,
				viewports->frame->is_mlx_object);
		image = viewports->images_to_render;
		while (image)
		{
			project = image->origin;
			if (viewports->camera)
			{
				cam = *viewports->camera;
				project = (t_v2d){project.x + cam.origin.x - cam.position.x,
					project.y + cam.origin.y - cam.position.y};
			}
			viewports->frame = set_pixels(viewports->frame, image, project);
			image = image->next;
		}
		viewports = viewports->next;
	}
}

#if BUILD_OS == MACOS

void	mlxge_render(void *mlx_inst, void *mlx_win, t_render_layer *layers)
{
	t_image	*win_frame;

	win_frame = clear_layer_frame(layers->frame, layers->frame->is_mlx_object);
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, win_frame->mlx_ptr);
	while (layers->next)
	{
		layers = layers->next;
		layers->frame = clear_layer_frame(layers->frame,
				layers->frame->is_mlx_object);
		update_layer_viewports(layers->viewport_list);
		draw_layer_frame(layers->z_buffer_tree, layers->frame);
		set_pixels(win_frame, layers->frame, layers->frame->origin);
	}
	mlx_put_image_to_window(mlx_inst, mlx_win, win_frame->mlx_ptr, 0, 0);
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, mlx_win);
}

#elif BUILD_OS == LINUX

void	mlxge_render(void *mlx_inst, void *mlx_win, t_render_layer *layers)
{
	t_image	*win_frame;

	win_frame = clear_layer_frame(layers->frame, layers->frame->is_mlx_object);
	while (layers->next)
	{
		layers = layers->next;
		layers->frame = clear_layer_frame(layers->frame,
				layers->frame->is_mlx_object);
		update_layer_viewports(layers->viewport_list);
		draw_layer_frame(layers->z_buffer_tree, layers->frame);
		set_pixels(win_frame, layers->frame, layers->frame->origin);
	}
	mlx_put_image_to_window(mlx_inst, mlx_win, win_frame->mlx_ptr, 0, 0);
}

#endif
