/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:42:06 by lmells            #+#    #+#             */
/*   Updated: 2023/12/13 17:42:34 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_STRUCT_H
# define IMAGE_STRUCT_H

# include <stdlib.h>
# include <stdbool.h>
# include "dimensions.h"
# include "vector.h"

typedef struct s_image_list
{
	t_v2d						origin;
	t_dimensions				size;
	int							bg_colour;
	bool						is_mlx_object;
	int							ctx[3];
	int							z_index;
	void						*mlx_ptr;
	int							*buff;
	struct s_image_list			*next;
}	t_image;

void	mlxge_destroy_image(t_image *image);

#endif
