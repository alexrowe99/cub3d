/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_quad.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:42:06 by lmells            #+#    #+#             */
/*   Updated: 2023/10/27 12:38:12 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_QUAD_H
# define IMAGE_QUAD_H

# include <stdlib.h>
# include <stdbool.h>
# include "dimensions.h"

typedef struct s_image_quad_list
{
	int							ox;
	int							oy;
	int							ctx[3];
	uint32_t					bg_colour;
	t_dimensions				size;
	bool						is_mlx_object;
	void						*mlx_ptr;
	uint32_t					*buff;
	struct s_image_quad_list	*next;
}	t_img_quad;

void	mlxge_destroy_image_quad(t_img_quad *ptr);

#endif
