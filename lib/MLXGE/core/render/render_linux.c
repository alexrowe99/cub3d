/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_linux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 09:20:53 by lmells            #+#    #+#             */
/*   Updated: 2023/12/18 16:04:03 by lmells           ###   ########.fr       */
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
	t_v2d		projection;
	t_image		*image;

	while (viewports)
	{
		viewports->frame = clear_layer_frame(viewports->frame,
				viewports->frame->is_mlx_object);
		image = viewports->images_to_render;
		while (image)
		{
			projection = image->origin;
			if (viewports->camera)
			{
				t_cam_ortho2d	cam = *viewports->camera;
				projection = (t_v2d){projection.x + cam.origin.x - cam.position.x,
						projection.y + cam.origin.y - cam.position.y};
			}
			viewports->frame = set_pixels(viewports->frame, image, projection);
			image = image->next;
		}
		viewports = viewports->next;
	}
}

void	mlxge_render(void *mlx_inst, void *mlx_win, t_render_layer *layers)
{
	t_image	*win_frame;

	// mlxge_log(DEBUG, "In Render Loop");
	win_frame = clear_layer_frame(layers->frame, layers->frame->is_mlx_object);
	while (layers->next)
	{
		layers = layers->next;
		layers->frame = clear_layer_frame(layers->frame,
				layers->frame->is_mlx_object);
		// if (layers->viewport_list)
		update_layer_viewports(layers->viewport_list);
		draw_layer_frame(layers->z_buffer_tree, layers->frame);
		set_pixels(win_frame, layers->frame, layers->frame->origin);
	}
	mlx_put_image_to_window(mlx_inst, mlx_win, win_frame->mlx_ptr, 0, 0);
	// mlxge_destroy();
}
