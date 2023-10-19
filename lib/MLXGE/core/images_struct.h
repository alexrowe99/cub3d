/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 09:22:27 by lmells            #+#    #+#             */
/*   Updated: 2023/10/19 19:13:02 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGES_STRUCT_H
# define IMAGES_STRUCT_H

# define OS_MacOS 1
# define OS_Linux 2
// # ifndef BUILD_OS
// #  define BUILD_OS OS_Linux
// # endif
# ifdef BUILD_OS
#  if BUILD_OS == OS_Linux
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
	// bool						updated;
	// void						(*redraw_image)(struct s_mlxge_image_list *);
	struct s_mlxge_image_list	*next;
};

typedef struct s_normalised_image_quad
{
	t_v2i	old_start;
	t_v2i	old_end;
	t_v2i	start;
	t_v2i	end;
}	t_normalised_quad;

typedef struct s_mlxge_image_list	t_image;

#endif
