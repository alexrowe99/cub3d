/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:12:43 by lmells            #+#    #+#             */
/*   Updated: 2023/10/17 16:26:32 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vector_2_int
{
	int	x;
	int	y;
}	t_v2i;

typedef struct s_vector_2_double
{
	double	x;
	double	y;
}	t_v2d;

t_v2d	v2d(double x, double y);
t_v2d	v2d_sum(t_v2d a, t_v2d b);
t_v2d	v2d_scale(t_v2d a, double t);

t_v2i	v2i(int x, int y);

t_v2i	v2d_to_v2i(t_v2d a);

#endif
