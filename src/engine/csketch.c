/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csketch.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:56:14 by lmells            #+#    #+#             */
/*   Updated: 2023/09/23 15:03:45 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <libftall.h>

static void	set_pixel(uint32_t *pixel, uint32_t colour)
{
	*pixel = colour;
}

static void	push_frame_buffer(uint32_t *pixel_buffer, t_v2i frame_size,
				t_img *image)
{
	t_v2i	pos;
	t_v2i	off;

	pos = v2i(-1, -1);
	while (++pos.y < image->dim.y)
	{
		off.y = pos.y + image->orig.y;
		if (0 <= off.y && off.y < frame_size.y)
		{
			pos.x = -1;
			while (++pos.x < image->dim.x)
			{
				off.x = pos.x + image->orig.x;
				if (0 <= off.x && off.x < frame_size.x)
					set_pixel(&pixel_buffer[off.y * frame_size.x + off.x],
						image->pbuff[pos.y * image->dim.x + pos.x]);
			}	
		}
	}
}

// ----- API -------------------------------------------------------------------

void	engine_render_csketch(void)
{
	t_mlx_inst		*mlx;
	t_img			*win_img;
	t_layer			*win_layer;
	t_layer_list	*layer_list;

	mlx = get_engine()->mlx;
	win_layer = get_engine()->render_layers->layer;
	win_img = win_layer->image;
	if (win_layer->updated)
	{
		engine_debug("Pushing layer images to window frame..");
		ft_bzero(win_img->pbuff,
				win_img->dim.x * win_img->dim.y * sizeof(uint32_t));
		layer_list = get_engine()->render_layers->next;
		while (layer_list)
		{
			push_frame_buffer(win_img->pbuff, win_img->dim,
				layer_list->layer->image);
			layer_list = layer_list->next;
		}
		win_layer->updated = false;
	}
	mlx_put_image_to_window(mlx->inst, mlx->win, win_img->mlx_img_ptr, 0, 0);
}

void	engine_csketch_fill(uint32_t *pixels, int w, int h, uint32_t colour)
{
	int	i;

	i = w * h;
	while (i--)
		pixels[i] = colour;
}

void	engine_redraw_csketch(void)
{
	get_engine()->render_layers->layer->updated = true;
}
