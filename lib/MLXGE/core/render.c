/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:33:59 by lmells            #+#    #+#             */
/*   Updated: 2023/10/17 19:21:33 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <render.h>

static int	sign(int val)
{
	return ((val > 0) - (val < 0));
}

static void	swap(int *v1, int *v2)
{
	int	tmp;

	tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}

static bool	mlxge_normalise_quad(t_v2i img_origin, t_dimensions img_size,
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

static uint32_t	*set_pixels(t_frame *frame, uint32_t *img_buff,
					t_v2i img_origin, t_dimensions img_size)
{
	int				colour;
	t_v2i			offset;
	int				x;
	int				y;

	t_normalised_quad	render_quad;

	if (!mlxge_normalise_quad(img_origin, img_size, frame->dim, &render_quad))
		return ((void *)0);
	// fprintf(stderr, "-------------------------------------------------------\n");
	// fprintf(stderr, "Frame : %ix%i ; origin : (X = %i, Y = %i)\n", frame->dim.width, frame->dim.height, frame->orig.x, frame->orig.y);
	// fprintf(stderr, "Image : %ix%i ; origin : (X = %i, Y = %i)\n", img_size.width, img_size.height, img_origin.x, img_origin.y);
	// fprintf(stderr, "\n");
	// fprintf(stderr, "RenderQuad : OrigStart (X = %i, Y = %i) ; OrigEnd : (X = %i, Y = %i)\n", render_quad.old_start.x, render_quad.old_start.y, render_quad.old_end.x, render_quad.old_end.y);
	// fprintf(stderr, "RenderQuad : Start (X = %i, Y = %i) ; End : (X = %i, Y = %i)\n", render_quad.start.x, render_quad.start.y, render_quad.end.x, render_quad.end.y);
	// fprintf(stderr, "\n");
	y = render_quad.start.y - 1;
	while (++y <= render_quad.end.y)
	{
		x = render_quad.start.x - 1;
		while (++x <= render_quad.end.x)
		{
			offset = (t_v2i){
				.x = x - render_quad.old_start.x,
				.y = y - render_quad.old_start.y
			};
			// if (offset.x == 0 && offset.y == 0)
			// {
			// 	fprintf(stderr, "Image Buff Index: (%i x %i + %i) = %i\n", offset.y, img_size.width, offset.x, offset.y * img_size.width + offset.x);
			// 	fprintf(stderr, "Frame Buff Index: (%i x %i + %i) = %i\n", y, frame->dim.width, x, y * frame->dim.width + x);
			// }
			colour = (int)img_buff[offset.y * img_size.width + offset.x];
			if (colour != (int)0xFF000000)
				frame->buff[y * frame->dim.width + x] = colour;
		}
	}
	// fprintf(stderr, "\n");
	// fprintf(stderr, "Image Buff Index: (%i x %i + %i) = %i\n", offset.y, img_size.width, offset.x, offset.y * img_size.width + offset.x);
	// fprintf(stderr, "Frame Buff Index: (%i x %i + %i) = %i\n", y - 1, frame->dim.width, x - 1, (y - 1) * frame->dim.width + (x - 1));
	// fprintf(stderr, "-------------------------------------------------------\n\n");
	
	// y = -1;
	// while (++y < img_size.height)
	// {
	// 	offset.y = y + img_origin.y;
	// 	if (offset.y >= 0 && offset.y < frame->dim.height)
	// 	{
	// 		x = -1;
	// 		while (++x < img_size.width)
	// 		{
	// 			offset.x = x + img_origin.x;
	// 			if (offset.x >= 0 && offset.x < frame->dim.width)
	// 			{
	// 				colour = (int)img_buff[y * img_size.width + x];
	// 				if (colour != (int)0xFF000000)
	// 					frame->buff[offset.y * frame->dim.width + offset.x] = colour;
	// 			}
	// 		}	
	// 	}
	// }
	return (frame->buff);
}

static void	redraw_frame(t_frame *frame, t_image *img_list, t_viewport *viewport)
{
	t_image	*img;
	t_v2i	project;

	img = img_list;
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
		{
			ft_bzero(layer_frame->buff, layer_frame->dim.width * layer_frame->dim.height * sizeof(uint32_t));
			redraw_frame(layer_frame, layers->image_list, layers->viewport);
			layers->has_updated_images = false;
		}
		set_pixels(render, layer_frame->buff, layer_frame->orig, layer_frame->dim);
		layers = layers->next;
	}
	// mlxge_log(INFO, "Image Rendered!");
	// mlxge_destroy();
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
