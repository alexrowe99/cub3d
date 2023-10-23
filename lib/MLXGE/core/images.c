/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 09:47:30 by lmells            #+#    #+#             */
/*   Updated: 2023/10/21 17:13:44 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>

// Allocates pixel buffer for MLXGE image.
// Only allocates for a image that is not owned by MiniLibX.
static void	*mlxge_alloc_pixel_buff(t_image *frame)
{
	size_t	bytes;

	bytes = frame->dim.width * frame->dim.height;
	frame->buff = malloc((bytes + 1) * sizeof(uint32_t));
	if (!frame->buff)
	{
		mlxge_log(ERROR, "Failed to create layer frame because : "\
			"Couldn't allocate memory for pixel buffer");
		free(frame);
		return ((void *)0);
	}
	return (frame);
}

void	*mlxge_new_frame(int origin_x, int origin_y, int width, int height,
			void *mlx_image)
{
	int			ctx[3];
	t_image		*frame;

	frame = malloc(sizeof(t_image));
	if (!frame)
	{
		mlxge_log(ERROR, "Failed to create layer frame because : "\
			"Couldn't allocate memory");
		return ((void *)0);
	}
	frame->mlx_id = (void *)0;
	frame->next = (void *)0;
	frame->orig = v2i(origin_x, origin_y);
	frame->dim = dimensions(width, height);
	if (mlx_image)
	{
		frame->mlx_id = mlx_image;
		frame->buff = (uint32_t *)mlx_get_data_addr(mlx_image, &ctx[0], &ctx[1],
					&ctx[2]);
		mlxge_fill(frame, 0xFF000000);
		return (frame);
	}
	frame = mlxge_alloc_pixel_buff(frame);
	if (frame)
		mlxge_fill(frame, 0xFF000000);
	return ((void *)frame);
}

void	mlxge_destroy_images(void *img_list_ptr)
{
	t_image	*img_list;
	t_image	*node;

	img_list = (t_image *)img_list_ptr;
	while (img_list)
	{
		node = img_list;
		img_list = img_list->next;
		if (!node->mlx_id)
			free(node->buff);
		free(node);
	}
}

static void	push_image_list_back(t_image *img, t_image **list)
{
	t_image	*node;

	node = *list;
	if (!node)
	{
		*list = img;
		return ;
	}
	while (node->next)
		node = node->next;
	node->next = img;
}

// ----- API -------------------------------------------------------------------

void	*mlxge_new_image(void **img_list_ptr, int orig_x, int orig_y,
			int width, int height)
{
	size_t	bytes;
	t_image	*img;

	img = ft_calloc(1, sizeof(t_image));
	if (img)
	{
		bytes = width * height;
		img->orig = v2i(orig_x, orig_y);
		img->dim = dimensions(width, height);
		img->buff = malloc((bytes + 1) * sizeof(uint32_t));
		if (!img->buff)
		{
			mlxge_destroy_images(img);
			return ((void *)img);
		}
		mlxge_set_bg_colour(img, 0xFF000000);
		push_image_list_back(img, (t_image **)img_list_ptr);
	}
	return ((void *)img);
}

void	mlxge_move_image_center_frame(void *img_ptr, void *frame_ptr)
{
	t_image	*img;
	t_frame	*frame;

	img = (t_image *)img_ptr;
	frame = (t_frame *)frame_ptr;
	img->orig = v2i(frame->dim.width/2 - img->dim.width/2,
				frame->dim.height/2 - img->dim.height/2);
}

void	mlxge_move_frame_center_window(void *frame_ptr)
{
	t_dimensions	win_dim;
	t_frame			*frame;

	frame = (t_frame *)frame_ptr;
	win_dim = get_mlxge_core()->win->dim;
	frame->orig = v2i(win_dim.width / 2 - frame->dim.width / 2,
					win_dim.height / 2 - frame->dim.height / 2);
}

void	mlxge_image_translate(void *img_ptr, int offset_x, int offset_y)
{
	t_v2i	img_orig;

	img_orig = ((t_image *)img_ptr)->orig;
	((t_image *)img_ptr)->orig = (t_v2i){.x=img_orig.x+offset_x, .y=img_orig.y+offset_y};
}

void	mlxge_set_bg_colour(void *img_ptr, int colour_rgb)
{
	((t_image *)img_ptr)->bg_colour = colour_rgb;
	mlxge_fill(img_ptr, colour_rgb);
}
