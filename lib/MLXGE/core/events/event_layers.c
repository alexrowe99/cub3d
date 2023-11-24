/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_layers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 20:50:06 by lmells            #+#    #+#             */
/*   Updated: 2023/10/27 20:50:51 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <events.h>
#include <core.h>

void	mlxge_destroy_event_layers(t_event_layer *list)
{
	t_event_layer	*node;

	node = list;
	while (node)
	{
		list = list->next;
		free(node);
		node = list;
	}
}

static inline void	push_event_layer_list_front(t_event_layer *layer,
						t_event_layer **list)
{
	t_event_layer	*head;

	head = *list;
	layer->next = head;
	*list = layer;
}

t_event_layer	*mlxge_load_event_layers(t_layer *render_list)
{
	t_event_layer	*layer;
	t_event_layer	*event_list;

	event_list = get_core()->event_layers;
	while (render_list)
	{
		layer = ft_calloc(1, sizeof(t_event_layer));
		if (!layer)
		{
			mlxge_log(ERROR, "Failed to load MLXGE event layers because : "\
				"Couldn't allocate memory");
			return ((void *)0);
		}
		layer->layer_ref = render_list;
		push_event_layer_list_front(layer, &event_list);
		render_list = render_list->next;
	}
	return (event_list);
}
