/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 19:09:12 by lmells            #+#    #+#             */
/*   Updated: 2023/09/23 09:51:06 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core/vector.h>

t_v2i	v2i(int x, int y)
{
	return ((t_v2i){.x = x,
					.y = y});
}

t_v2d	v2d(double x, double y)
{
	return ((t_v2d){.x = x,
					.y = y});
}

t_v2d	v2i_to_v2d(t_v2i e)
{
	return ((t_v2d){.x = e.x,
					.y = e.y});
}

t_v2i	v2d_to_v2i(t_v2d e)
{
	return ((t_v2i){.x = e.x,
					.y = e.y});
}

t_v2i	v2i_sum(t_v2i a, t_v2i b)
{
	return ((t_v2i){.x = a.x + b.x,
					.y = a.y + b.y});
}
