/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mac.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 09:20:53 by lmells            #+#    #+#             */
/*   Updated: 2023/10/27 18:25:19 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <render.h>

static inline t_img_quad	*clear_layer_frame(t_img_quad *frame,
								bool is_mlx_object)
{
	void	*mlx_instance;

	if (is_mlx_object)
	{
		mlx_instance = get_core()->mlx_inst_ptr;
		if (frame->mlx_ptr)
			mlx_destroy_image(mlx_instance, frame->mlx_ptr);
		frame->mlx_ptr = mlx_new_image(mlx_instance,
								frame->size.width,
								frame->size.height);
		frame->buff = (uint32_t *)mlx_get_data_addr(frame->mlx_ptr,
								&frame->ctx[0], &frame->ctx[1], &frame->ctx[2]);
	}
	mlxge_fill(frame, frame->bg_colour);
	return (frame);
}

static inline void	update_viewports(t_img_quad *update_frame,
						t_viewport *viewports)
{
	t_img_quad	*image;

	while (viewports)
	{
		viewports->frame = clear_layer_frame(viewports->frame,
						viewports->frame->is_mlx_object);
		image = viewports->images_to_render;
		while (image)
		{
			viewports->frame = set_pixels(viewports->frame, image);
			image = image->next;
		}
		update_frame = set_pixels(update_frame, viewports->frame);
		viewports = viewports->next;
	}
}

void	mlxge_render(void *mlx_inst, void *mlx_win, t_render_layer *layers)
{
	t_img_quad	*image;
	t_img_quad	*win_frame;

	win_frame = clear_layer_frame(layers->frame, layers->frame->is_mlx_object);
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, win_frame->mlx_ptr);
	while (layers->next)
	{
		layers = layers->next;
		layers->frame = clear_layer_frame(layers->frame,
						layers->frame->is_mlx_object);
		if (layers->viewport_list)
			update_viewports(layers->frame, layers->viewport_list);
		else
		{
			image = layers->images_to_render;
			while (image)
			{
				layers->frame = set_pixels(layers->frame, image);
				image = image->next;
			}
		}
		set_pixels(win_frame, layers->frame);
	}
	mlx_put_image_to_window(mlx_inst, mlx_win, win_frame->mlx_ptr, 0, 0);
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, mlx_win);
}
