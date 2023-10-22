/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:33:59 by lmells            #+#    #+#             */
/*   Updated: 2023/10/22 20:05:43 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <render.h>

static inline int	sign(int val)
{
	return ((val > 0) - (val < 0));
}

static inline void	swap(int *v1, int *v2)
{
	int	tmp;

	tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}

static inline bool	mlxge_normalise_quad(t_v2i img_origin, t_dimensions img_size,
						t_dimensions quad_size, t_normalised_quad *quad)
{
	if (!img_size.width || !img_size.height)
		return (false);
	quad->old_start = (t_v2i){.x=img_origin.x, .y=img_origin.y};
	quad->old_end = (t_v2i){
		.x = quad->old_start.x + sign(img_size.width) * (abs(img_size.width) - 1),
		.y = quad->old_start.y + sign(img_size.height) * (abs(img_size.height) - 1),
	};
	if (quad->old_start.x > quad->old_end.x)
		swap(&quad->old_start.x, &quad->old_end.x);
	if (quad->old_start.y > quad->old_end.y)
		swap(&quad->old_start.y, &quad->old_end.y);
	if (quad->old_start.x >= quad_size.width || quad->old_end.x < 0
		|| quad->old_start.y >= quad_size.height || quad->old_end.y < 0)
		return (false);
	quad->start = quad->old_start;
	quad->end = quad->old_end;
	if (quad->start.x < 0)
		quad->start.x = 0;
	if (quad->start.y < 0)
		quad->start.y = 0;
	if (quad->end.x >= quad_size.width)
		quad->end.x = quad_size.width - 1;
	if (quad->end.y >= quad_size.height)
		quad->end.y = quad_size.height - 1;
	return (true);
}

uint32_t	*set_pixels(t_frame *frame, uint32_t *img_buff, t_v2i img_origin,
				t_dimensions img_size)
{
	int					colour;
	t_v2i				offset;
	t_v2i				p;
	t_normalised_quad	render_quad;

	if (!mlxge_normalise_quad(img_origin, img_size, frame->dim, &render_quad))
		return ((void *)0);
	p.y = render_quad.start.y - 1;
	while (++p.y <= render_quad.end.y)
	{
		p.x = render_quad.start.x - 1;
		while (++p.x <= render_quad.end.x)
		{
			offset = (t_v2i){
				.x = p.x - render_quad.old_start.x,
				.y = p.y - render_quad.old_start.y
			};
			colour = (int)img_buff[offset.y * img_size.width + offset.x];
			if (colour != (int)0xFF000000)
				frame->buff[p.y * frame->dim.width + p.x] = colour;
		}
	}
	return (frame->buff);
}

void	redraw_frame(t_frame *frame, t_image *img_list, t_viewport *viewport)
{
	t_image	*img;
	t_v2i	project;

	img = img_list;
	mlxge_fill(frame, frame->bg_colour);
	while (img)
	{
		project = (t_v2i){.x = img->orig.x, .y = img->orig.y};
		if (viewport)
		{
			project = (t_v2i){
				.x = img->orig.x + viewport->camera.offset.x,
				.y = img->orig.y + viewport->camera.offset.y,
			};
		}
		if (!set_pixels(frame, img->buff, project, img->dim))
			return ;
		img = img->next;
	}
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
			int colour_rgb)
{
	t_image *img;
	t_v2i	begin;
	t_v2i	end;
	t_v2i	d;

	img = (t_image *)img_ptr;
	end = v2i(cx + radius, cy + radius);
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
						img->buff[begin.y * img->dim.width + begin.x] = (uint32_t)colour_rgb;
				}
			}
		}
	}
}

void	mlxge_draw_rect_fill(void *img_ptr, t_v2i start, t_v2i end,
			int colour_rgb)
{
	t_v2i	p;
	t_image *img;

	img = (t_image *)img_ptr;
	p.y = start.y - 1;
	while (++p.y < end.y)
	{
		if (0 <= p.y)
		{
			p.x = start.x - 1;
			while (++p.x < end.x)
				if (0 <= p.x)
					img->buff[p.y * img->dim.width + p.x] = (uint32_t)colour_rgb;
		}
	}
}
