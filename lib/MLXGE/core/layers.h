/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layers.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:34:16 by lmells            #+#    #+#             */
/*   Updated: 2023/12/13 17:51:44 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAYERS_H
# define LAYERS_H

# include "events.h"
# include "image_struct.h"
# include "viewport.h"

typedef struct s_layer_list
{
	int							(*on_update)(struct s_layer_list *, double timestep);
	t_event						*events[COUNT_EVENT_TYPES];
	t_image					*frame;
	struct s_image_list	*images_to_render;
	t_viewport					*viewport_list;
	struct s_layer_list			*next;
}	t_layer;

typedef t_layer	t_render_layer;

typedef struct s_event_layer_list
{
	t_layer						*layer_ref;
	struct s_event_layer_list	*next;
}	t_event_layer;

int	mlxge_push_layer(t_layer *layer);

#endif
