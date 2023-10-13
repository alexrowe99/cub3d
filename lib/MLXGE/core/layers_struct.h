/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layers_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:15:29 by lmells            #+#    #+#             */
/*   Updated: 2023/10/13 11:15:42 by lmells           ###   ########.fr       */
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
	void				**event_list; // Point to the layer's event's - ?? Override polling for that input ??
	int					(*on_update)(struct s_layer_list *); // Will be passed a reference pointer to itself.
	void				*frame;
	void				*image_list;
	bool				has_updated_images;
	struct s_layer_list	*next;
}	t_layer;

#endif
