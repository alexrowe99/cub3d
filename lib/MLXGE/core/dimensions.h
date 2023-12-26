/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dimensions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:23:26 by lmells            #+#    #+#             */
/*   Updated: 2023/12/24 12:37:25 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIMENSIONS_H
# define DIMENSIONS_H

typedef struct s_dimensions_2D
{
	int	width;
	int	height;
}	t_dimensions;

t_dimensions	dimension_2d(int w, int h);

#endif
