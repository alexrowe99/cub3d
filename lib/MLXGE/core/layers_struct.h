/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layers_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:15:29 by lmells            #+#    #+#             */
/*   Updated: 2023/10/12 10:17:15 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAYERS_STRUCT_H
# define LAYERS_STRUCT_H

# include <stdbool.h>
# include <stdlib.h>

# include "dimensions.h"
# include "vector.h"

struct s_mlxge_layer_frame
{
	t_v2i			origin;
	t_dimensions	dim;
	uint32_t		*buff;
};

typedef struct s_layer_list
{
	void				**event_list; // Point to the layer's event's - ?? Override polling for that input ??
	int					(*on_update)(struct s_layer_list *); // Will be passed a reference pointer to itself.
	// bool				updated;
	void				*frame;
	struct s_layer_list	*next;
}	t_layer;

#endif
