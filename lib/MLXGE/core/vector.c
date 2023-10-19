/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:13:56 by lmells            #+#    #+#             */
/*   Updated: 2023/10/17 16:26:30 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector.h>

t_v2i	v2i(int x, int y)
{
	return ((t_v2i){.x = x, .y = y});
}

t_v2d	v2d(double x, double y)
{
	return ((t_v2d){.x = x, .y = y});
}

t_v2d	v2d_sum(t_v2d a, t_v2d b)
{
	return ((t_v2d){.x = a.x + b.x, .y = a.y + b.y});
}

t_v2i	v2d_to_v2i(t_v2d a)
{
	return ((t_v2i){.x = a.x, .y = a.y});
}

t_v2d	v2d_scale(t_v2d a, double t)
{
	return ((t_v2d){.x = a.x * t, .y = a.y * t});
}
