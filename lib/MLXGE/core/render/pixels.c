/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 20:08:49 by lmells            #+#    #+#             */
/*   Updated: 2023/12/13 17:42:34 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>
#include <dimensions.h>

void	put_pixel(t_image *image, int x, int y, int colour)
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

t_image	*set_pixels(t_image *frame, t_image *image,
				t_v2d img_origin)
{
	t_v2i	p;
	t_v2i	offset;
	int		colour;

	p.y = -1;
	while (++p.y < image->size.height)
	{
		offset.y = p.y + (int)img_origin.y;
		if (0 <= offset.y && offset.y < frame->size.height)
		{
			p.x = -1;
			while (++p.x < image->size.width)
			{
				offset.x = p.x + (int)img_origin.x;
				if (0 <= offset.x && offset.x < frame->size.width)
				{
					colour = image->buff[p.y * image->size.width + p.x];
					put_pixel(frame, offset.x, offset.y, colour);
				}
			}
		}
	}
	return (frame);
}
