/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:27:57 by lmells            #+#    #+#             */
/*   Updated: 2023/10/27 21:04:57 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <events.h>

int	mlxge_handle_event(int code, t_event_layer *event_layers,
				enum e_event_types type)
{
	t_event	*event_list;

	while (event_layers)
	{
		event_list = event_layers->layer_ref->events[type];
		while (event_list)
		{
			if (event_list->code == code)
				event_list->action(event_list->param);
			event_list = event_list->next;
		}
		event_layers = event_layers->next;
	}
	return (1);
}

void	mlxge_destroy_events(t_event *list)
{
	t_event	*node;

	node = list;
	while (node)
	{
		list = list->next;
		free(node);
		node = list;
	}
}

// ---- API --------------------------------------------------------------------

void	mlxge_push_event(t_event *event, t_event **list)
{
	t_event	*node;

	node = list[event->type];
	if (!node)
	{
		list[event->type] = event;
		return ;
	}
	while (node->next)
		node = node->next;
	node->next = event;
}
