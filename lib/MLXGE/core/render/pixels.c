/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 20:08:49 by lmells            #+#    #+#             */
/*   Updated: 2023/10/28 20:34:12 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>
#include <dimensions.h>

static inline void	put_pixel(t_img_quad *image, int x, int y, int colour)
{
	char	*buff;
	char	*dst;

	if (colour == (int)0xFF000000)
		return ;
	if (!image->is_mlx_object)
	{
		image->buff[y * image->size.width + x] = colour;
		return ;
	}
	buff = (char *)image->buff;
	dst = buff + (y * image->ctx[1] + x * (image->ctx[0] / 8));
	*(unsigned int *)dst = colour;
}

t_img_quad	*set_pixels(t_img_quad *frame, t_img_quad *image)
{
	int	x;
	int	y;
	int	ox;
	int	oy;
	int	colour;

	y = -1;
	while (++y < image->size.height)
	{
		oy = y + image->origin.y;
		if (0 < oy && oy <= frame->size.height)
		{
			x = -1;
			while (++x < image->size.width)
			{
				ox = x + image->origin.x;
				if (0 <= ox && ox < frame->size.width)
				{
					colour = image->buff[y * image->size.width + x];
					put_pixel(frame, ox, oy, colour);
				}
			}
		}
	}
	return (frame);
}
