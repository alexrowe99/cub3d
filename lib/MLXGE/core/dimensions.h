/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dimensions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:30:08 by lmells            #+#    #+#             */
/*   Updated: 2023/10/09 11:43:11 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIMENSIONS_H
# define DIMENSIONS_H

typedef struct s_dimensions
{
	int width;
	int	height;
}	t_dimensions;

t_dimensions	dimensions(int w, int h);

#endif
