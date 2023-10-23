/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layers_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:15:29 by lmells            #+#    #+#             */
/*   Updated: 2023/10/22 13:07:52 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAYERS_STRUCT_H
# define LAYERS_STRUCT_H

# include <stdbool.h>
# include <stdlib.h>

# include "dimensions.h"
# include "vector.h"

typedef struct s_layer_list
{
	bool				has_updated_images;
	void				**event_list; // Point to the layer's event's - ?? Override polling for that input ??
	int					(*on_update)(struct s_layer_list *);//, double);//, double dt); // Will be passed a reference pointer to itself.
	void				*frame;
	void				*image_list;
	struct s_layer_list	*next;
	// Remove me after testing - figure out viewport & camera structure.
	// void				*viewport;
}	t_layer;

typedef struct s_camera
{
	t_v2i	pos;
	t_v2d	offset;
}	t_camera;

typedef struct s_viewport
{
	t_v2d			orig;
	t_dimensions	dim;
	t_layer			*render;
	t_camera		camera;
}	t_viewport;

#endif
