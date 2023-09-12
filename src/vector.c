/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 19:09:12 by lmells            #+#    #+#             */
/*   Updated: 2023/09/11 16:50:48 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_v2d	v2i_to_v2d(t_v2i e)
{
	t_v2d	v;

	v.x = e.x;
	v.y = e.y;
	return (v);
}

t_v2i	v2d_to_v2i(t_v2d e)
{
	t_v2i	v;

	v.x = e.x;
	v.y = e.y;
	return (v);
}

t_v2i	v2i(int x, int y)
{
	t_v2i	v;

	v.x = x;
	v.y = y;
	return (v);
}

t_v2d	v2d(double x, double y)
{
	t_v2d	v;

	v.x = x;
	v.y = y;
	return (v);
}
