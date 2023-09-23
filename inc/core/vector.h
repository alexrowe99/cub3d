/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:19:57 by lmells            #+#    #+#             */
/*   Updated: 2023/09/23 09:48:29 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec2_int
{
	int		x;
	int		y;
}	t_v2i;

typedef struct s_vec2_double
{
	double	x;
	double	y;
}	t_v2d;

t_v2i		v2i(int x, int y);
t_v2i		v2i_sum(t_v2i a, t_v2i b);
t_v2i		v2d_to_v2i(t_v2d e);

t_v2d		v2d(double x, double y);
t_v2d		v2i_to_v2d(t_v2i e);

#endif
