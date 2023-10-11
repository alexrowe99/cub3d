/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:33:59 by lmells            #+#    #+#             */
/*   Updated: 2023/10/10 15:22:01 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <render.h>

static uint32_t	*set_pixels(uint32_t *render_buff, uint32_t *img_buff,
					t_v2i img_origin, t_dimensions img_size)
{
	t_dimensions	render;
	t_v2i			offset;
	int				x;
	int				y;

	render = get_mlxge_core()->win->dim;
	y = -1;
	while (++y < img_size.height)
	{
		offset.y = y + img_origin.y;
		if (offset.y >= 0 && offset.y < render.height)
		{
			x = -1;
			while (++x < img_size.width)
			{
				offset.x = x + img_origin.x;
				if (offset.x >= 0 && offset.x < render.width)
					render_buff[offset.y * render.width + offset.x] = img_buff[y * img_size.width + x];
			}	
		}
	}
	return (render_buff);
}

int	mlxge_render(t_layer *layers)
{
	struct  s_mlxge_window	*win;
	uint32_t				*render_buff;
	t_frame					*frame;

	win = get_mlxge_core()->win;
	render_buff = ((t_frame *)((t_layer *)win->layer)->frame)->buff;
	ft_bzero(render_buff, win->dim.width * win->dim.height);
	while (layers)
	{
		frame = (t_frame *)layers->frame;
		set_pixels(render_buff, frame->buff, frame->origin, frame->dim);
		layers = layers->next;
	}
	return (mlx_put_image_to_window(get_mlxge_core()->mlx, win->id_ptr,
			win->img, 0, 0));
}

// ----- API -------------------------------------------------------------------

void	mlxge_fill_frame(void *frame_ptr, uint32_t colour_rgb)
{
	size_t	i;
	t_frame	*frame;

	frame = (t_frame *)frame_ptr;
	i = frame->dim.width * frame->dim.height;
	while (i--)
		frame->buff[i] = colour_rgb;
}

void	mlxge_draw_circle(void *frame_ptr, int cx, int cy, int radius, uint32_t colour_rgb)
{
	t_frame *frame;
	t_v2i	begin;
	t_v2i	end;
	t_v2i	d;

	frame = (t_frame *)frame_ptr;
	end.x = cx + radius;
	end.y = cy + radius;
	begin.y = cy - radius;
	while (begin.y++ <= end.y)
	{
		if (0 <= begin.y && begin.y < frame->dim.height)
		{
			begin.x = cx - radius;
			while (begin.x++ <= end.x)
			{
				if (0 <= begin.x && begin.x < frame->dim.width)
				{
					d.x = begin.x - cx;
					d.y = begin.y - cy;
					if (d.x*d.x + d.y*d.y <= radius*radius)
						frame->buff[begin.y * frame->dim.width + begin.x] = colour_rgb;
				}
			}
		}
	}
// 	int			xit;
// 	t_v2i		p[2];
// 	p[0].x = cx - r;
// 	p[0].y = cy - r;
// 	p[1].x = cx + r;
// 	p[1].y = cy + r;
// 	while (p[0].y++ <= p[1].y)
// 	{
// 		if (0 <= p[0].y && p[0].y < (int)csketch->c_height)
// 		{
// 			xit = p[0].x;
// 			while (xit++ <= p[1].x && 0 <= xit && xit < (int)csketch->c_width)
// 			{
// 				if (((xit - cx)*(xit - cx)) + ((p[0].y - cy)*(p[0].y - cy)) <= r*r)
// 					csketch->image->pixels[p[0].y * csketch->c_width + xit] = colour;
// 			}
// 		}
// 	}
}
