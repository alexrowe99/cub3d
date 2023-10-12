/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:36:25 by lmells            #+#    #+#             */
/*   Updated: 2023/10/09 14:40:11 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>

// Allocates pixel buffer for MLXGE frame.
// Only allocates for a layer that is not owned by MiniLibX.
static void	*mlxge_alloc_pixel_buff(struct s_mlxge_layer_frame *frame)
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
	int							ctx[3];
	struct s_mlxge_layer_frame	*frame;

	frame = ft_calloc(1, sizeof(struct s_mlxge_layer_frame));
	if (!frame)
	{
		mlxge_log(ERROR, "Failed to create layer frame because : "\
			"Couldn't allocate memory");
		return ((void *)0);
	}
	frame->origin = (t_v2i){.x=origin_x,.y=origin_y};
	frame->dim = dimensions(width, height);
	if (!mlx_image)
		return (mlxge_alloc_pixel_buff(frame));
	frame->buff = (uint32_t *)mlx_get_data_addr(mlx_image, &ctx[0], &ctx[1],
					&ctx[2]);
	return ((void *)frame);
}

