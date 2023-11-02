/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 09:39:05 by lmells            #+#    #+#             */
/*   Updated: 2023/11/03 10:13:48 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>
#include <dimensions.h>

void	mlxge_fill(t_img_quad *image, int colour)
{
	int	size;

	size = image->size.width * image->size.height;
	while (size--)
		image->buff[size] = colour;
}

void	mlxge_draw_circle(t_img_quad *image, t_v2i center, int radius,
			int colour)
{
	t_v2i	d;
	t_v2i	s;
	t_v2i	e;

	e = (t_v2i){center.x + radius, center.y + radius};
	s.y = center.y - radius - 1;
	while (++s.y <= e.y)
	{
		if (0 <= s.y && s.y < image->size.height)
		{
			s.x = center.x - radius - 1;
			while (++s.x <= e.x)
			{
				if (0 <= s.x && s.x < image->size.width)
				{
					d = (t_v2i){s.x - center.x, s.y - center.y};
					if (d.x * d.x + d.y * d.y <= radius * radius)
						image->buff[s.y * image->size.width + s.x] = colour;
				}
			}
		}
	}
}

void	mlxge_fill_rect(t_img_quad *image, t_v2i start, t_v2i end,
			int colour)
{
	int	px;

	while (start.y < end.y)
	{
		px = start.x;
		while (px < end.x)
		{
			image->buff[start.y * image->size.width + px] = colour;
			px++;
		}
		start.y++;
	}
}
