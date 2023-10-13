/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:33:59 by lmells            #+#    #+#             */
/*   Updated: 2023/10/13 12:50:10 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <render.h>

static uint32_t	*set_pixels(t_frame *frame, uint32_t *img_buff,
					t_v2i img_origin, t_dimensions img_size)
{
	t_v2i			offset;
	int				x;
	int				y;

	y = -1;
	while (++y < img_size.height)
	{
		offset.y = y + img_origin.y;
		if (offset.y >= 0 && offset.y < frame->dim.height)
		{
			x = -1;
			while (++x < img_size.width)
			{
				offset.x = x + img_origin.x;
				if (offset.x >= 0 && offset.x < frame->dim.width)
					frame->buff[offset.y * frame->dim.width + offset.x] = img_buff[y * img_size.width + x];
			}	
		}
	}
	return (frame->buff);
}

static void	redraw_frame(t_frame *frame, t_image *img_list)
{
	t_image	*img;

	img = img_list;
	while (img)
	{
		set_pixels(frame, img->buff, img->orig, img->dim);
		img = img->next;
	}
}

int	mlxge_render(t_layer *layers)
{
	struct s_mlxge			*core;
	struct s_mlxge_window	*win;
	t_frame					*render;
	t_frame					*layer_frame;

	core = get_mlxge_core(); 
	win = core->win;
	render = (t_frame *)((t_layer *)win->layer)->frame;
	ft_bzero(render->buff, win->dim.width * win->dim.height * sizeof(uint32_t));
	while (layers)
	{
		layer_frame = (t_frame *)layers->frame;
		if (layers->has_updated_images)
			redraw_frame(layer_frame, layers->image_list);
		set_pixels(render, layer_frame->buff, layer_frame->orig, layer_frame->dim);
		layers = layers->next;
	}
	return (mlx_put_image_to_window(core->mlx, win->id_ptr, win->img, 0, 0));
}

// ----- API -------------------------------------------------------------------

void	mlxge_fill(void *img_ptr, uint32_t colour_rgb)
{
	size_t	i;
	t_image	*img;

	img = (t_image *)img_ptr;
	i = img->dim.width * img->dim.height;
	while (i--)
		img->buff[i] = colour_rgb;
}

void	mlxge_draw_circle(void *img_ptr, int cx, int cy, int radius,
			uint32_t colour_rgb)
{
	t_image *img;
	t_v2i	begin;
	t_v2i	end;
	t_v2i	d;

	img = (t_image *)img_ptr;
	end.x = cx + radius;
	end.y = cy + radius;
	begin.y = cy - radius;
	while (begin.y++ <= end.y)
	{
		if (0 <= begin.y && begin.y < img->dim.height)
		{
			begin.x = cx - radius;
			while (begin.x++ <= end.x)
			{
				if (0 <= begin.x && begin.x < img->dim.width)
				{
					d = v2i(begin.x - cx, begin.y - cy);
					if (d.x*d.x + d.y*d.y <= radius*radius)
						img->buff[begin.y * img->dim.width + begin.x] = colour_rgb;
				}
			}
		}
	}
}

void	mlxge_draw_rect_fill(void *img_ptr, t_v2i start, t_v2i end,
			uint32_t colour_rgb)
{
	t_v2i	p;
	t_image *img;

	img = (t_image *)img_ptr;
	p = start;
	while (p.y < end.y)
	{
		if (0 <= p.y)
		{
			p.x = start.x;
			while (p.x < end.x)
			{
				if (0 <= p.x)
					img->buff[p.y * img->dim.width + p.x] = colour_rgb;
				p.x++;
			}
		}
		p.y++;
	}
}
