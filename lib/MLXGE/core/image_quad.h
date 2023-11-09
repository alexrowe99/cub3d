/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_quad.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:42:06 by lmells            #+#    #+#             */
/*   Updated: 2023/11/06 19:07:13 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_QUAD_H
# define IMAGE_QUAD_H

# include <stdlib.h>
# include <stdbool.h>
# include "dimensions.h"
# include "vector.h"

typedef struct s_image_quad_list
{
	t_v2d						origin;
	t_dimensions				size;
	int							bg_colour;
	bool						is_mlx_object;
	void						*mlx_ptr;
	int							ctx[3];
	int							*buff;
	struct s_image_quad_list	*next;
}	t_img_quad;

void	mlxge_destroy_image_quad(t_img_quad *ptr);

#endif
