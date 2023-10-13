/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 09:22:27 by lmells            #+#    #+#             */
/*   Updated: 2023/10/13 11:31:19 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGES_STRUCT_H
# define IMAGES_STRUCT_H

# define BUILD_OS 1

# ifdef BUILD_OS
#  if BUILD_OS == 2
#   include <stdint.h>
#  endif
# endif

# include "vector.h"
# include "dimensions.h"

struct s_mlxge_image_list
{
	bool						mlx_img;	// Might just load and handle buffers myself...
	void						*mlx_id;	// Could possible check this for NULL then handle buffer.
	t_v2i						orig;
	t_dimensions				dim;
	uint32_t					*buff;
	struct s_mlxge_image_list	*next;
};

typedef struct s_mlxge_image_list	t_image;

#endif
