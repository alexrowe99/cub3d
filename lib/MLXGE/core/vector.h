/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:58:53 by lmells            #+#    #+#             */
/*   Updated: 2023/12/24 12:44:18 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vector_2_double
{
	double	x;
	double	y;
}	t_v2d;

typedef struct s_vector_2_int
{
	int		x;
	int		y;
}	t_v2i;

t_v2d	vector_2_double(double x, double y);
t_v2i	vector_2_int(int x, int y);

#endif
