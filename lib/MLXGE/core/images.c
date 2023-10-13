/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 09:47:30 by lmells            #+#    #+#             */
/*   Updated: 2023/10/13 13:25:24 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>

// Allocates pixel buffer for MLXGE image.
// Only allocates for a image that is not owned by MiniLibX.
static void	*mlxge_alloc_pixel_buff(t_image *frame)
{
	frame->buff = malloc((frame->dim.width * frame->dim.height + 1) * sizeof(uint32_t));
	if (!frame->buff)
	{
		mlxge_log(ERROR, "Failed to create layer frame because : "\
			"Couldn't allocate memory for pixel buffer");
		free(frame);
		return ((void *)0);
	}
	frame->buff[frame->dim.width * frame->dim.height] = 0;
	return ((void *)frame);
}

void	*mlxge_new_frame(int origin_x, int origin_y, int width, int height,
			void *mlx_image)
{
	int			ctx[3];
	t_image		*frame;

	frame = ft_calloc(1, sizeof(t_image));
	if (!frame)
	{
		mlxge_log(ERROR, "Failed to create layer frame because : "\
			"Couldn't allocate memory");
		return ((void *)0);
	}
	frame->orig = v2i(origin_x, origin_y);
	frame->dim = dimensions(width, height);
	if (!mlx_image)
		return (mlxge_alloc_pixel_buff(frame));
	frame->buff = (uint32_t *)mlx_get_data_addr(mlx_image, &ctx[0], &ctx[1],
					&ctx[2]);
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

// ----- API -------------------------------------------------------------------

void	*mlxge_new_image(void **img_list_ptr, int orig_x, int orig_y,
			int width, int height)
{
	t_image	*img;

	img = ft_calloc(1, sizeof(t_image));
	if (img)
	{
		img->orig = v2i(orig_x, orig_y);
		img->dim = dimensions(width, height);
		img->buff = ft_calloc(width * height + 1, sizeof(uint32_t));
		if (!img->buff)
		{
			mlxge_destroy_images(img);
			return ((void *)img);
		}
		img->next = (t_image *)*img_list_ptr;
		*img_list_ptr = img;
	}
	return ((void *)img);
}

void	mlxge_center_image(void *img_ptr, void *frame_ptr)
{
	t_image	*img;
	t_frame	*frame;

	img = (t_image *)img_ptr;
	frame = (t_frame *)frame_ptr;
	img->orig = v2i(frame->dim.width/2 - img->dim.width/2,
				frame->dim.height/2 - img->dim.height/2);
}
