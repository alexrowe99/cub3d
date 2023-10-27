/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 20:46:10 by lmells            #+#    #+#             */
/*   Updated: 2023/10/27 21:04:38 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <events.h>
#include <core.h>

static inline int	mlx_event_code(enum e_event_types event_type)
{
	static int	codes[COUNT_EVENT_TYPES];

	if (!codes[KEY_PRESS])
	{
		codes[KEY_PRESS] = ON_KEY_PRESS_EVENT;
		codes[KEY_RELEASE] = ON_KEY_RELEASE_EVENT;
		codes[DESTROY] = ON_DESTROY_EVENT;
	}
	return (codes[event_type]);
}

void	mlxge_load_mlx_event_hooks(void *mlx_win_ptr,
			t_event_layer *event_layers)
{
	int				i;
	t_event			*event;
	t_layer			*layer;
	t_event_layer	*list;

	list = event_layers;
	while (list)
	{
		layer = list->layer_ref;
		i = -1;
		while (++i < COUNT_EVENT_TYPES)
		{
			event = layer->events[i];
			while (event)
			{
				mlx_hook(mlx_win_ptr, mlx_event_code(event->type), event->code,
					event->handler, event_layers);
				event = event->next;
			}
		}
		list = list->next;
	}
}
