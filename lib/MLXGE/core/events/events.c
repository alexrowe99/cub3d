/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:27:57 by lmells            #+#    #+#             */
/*   Updated: 2023/10/30 15:12:17 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <events.h>

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

int	mlxge_handle_destroy_events(t_event_layer *layers_list)
{
	t_event	*event;

	while (layers_list)
	{
		event = layers_list->layer_ref->events[DESTROY];
		while (event)
		{
			event->handler(event->param);
			event = event->next;
		}
		layers_list = layers_list->next;
	}
	// mlxge_destroy();
	return (1);
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

t_event	*mlxge_new_destroy_event(int (*handler_funct)(void *), void *param)
{
	t_event	*destroy;

	destroy = ft_calloc(1, sizeof(t_event));
	if (!destroy)
	{
		mlxge_log(ERROR, "Failed to create a new MLXGE destroy event because :"\
			" Couldn't allocate memory");
		return ((void *)0);
	}
	destroy->type = DESTROY;
	destroy->handler = handler_funct;
	destroy->param = param;
	return (destroy);
}
