/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:27:57 by lmells            #+#    #+#             */
/*   Updated: 2023/10/25 17:17:58 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <events.h>

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

static int	mlxge_handle_event(int code, t_event_layer *event_layers,
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

static int	mlxge_handle_key_press(int keycode, void *param)
{
	return (mlxge_handle_event(keycode, (t_event_layer *)param, KEY_PRESS));
}

static int	mlxge_handle_key_release(int keycode, void *param)
{
	return (mlxge_handle_event(keycode, (t_event_layer *)param, KEY_RELEASE));
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

// ---- API --------------------------------------------------------------------

t_event	*mlxge_new_key_event(enum e_key_input_types input, int keycode,
			int (*action_func)(void *param), void *param)
{
	static int	(*handle_key_input[2])(int, void *);
	t_event		*event;

	if (!handle_key_input[PRESS])
	{
		handle_key_input[PRESS] = mlxge_handle_key_press;
		handle_key_input[RELEASE] = mlxge_handle_key_release;
	}
	event = ft_calloc(1, sizeof(t_event));
	if (!event)
	{
		mlxge_log(ERROR, "Failed to create new MLXGE key event because : "\
			"Couldn't allocate memory");
		return ((void *)0);	
	}
	event->type = input;
	event->code = keycode;
	event->handler = handle_key_input[input];
	event->action = action_func;
	event->param = param;
	return (event);
}

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
