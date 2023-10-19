/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:52:17 by lmells            #+#    #+#             */
/*   Updated: 2023/10/19 18:16:25 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <events.h>

static int	*mlx_event_codes(void)
{
	static int	codes[COUNT_EVENT_TYPES];

	if (!codes[ON_KEY_PRESS])
	{
		codes[ON_KEY_PRESS] = MLX_ON_KEY_PRESS;
		codes[ON_KEY_RELEASE] = MLX_ON_KEY_RELEASE;
		codes[ON_MOUSE_PRESS] = MLX_ON_MOUSE_PRESS;
		codes[ON_MOUSE_RELEASE] = MLX_ON_MOUSE_RELEASE;
		codes[ON_MOUSE_MOVE] = MLX_ON_MOUSE_MOVE;
		codes[ON_EXPOSE] = MLX_ON_EXPOSE;
		codes[ON_DESTROY] = MLX_ON_DESTROY;
	}
	return (codes);
}

static t_event_layer	*new_event_layer(void)
{
	t_event_layer	*layer;

	layer = malloc(1 * sizeof(t_event_layer));
	if (!layer)
	{
		mlxge_log(FATAL, "Failed to create MLXGE event layer because : "\
			"Couldn't allocate memory");
		exit(mlxge_destroy());
	}
	layer->next = (void *)0;
	return (layer);
}

static int	handle_events(int code, t_event_layer *list, int event_type)
{
	t_layer			*layer;
	t_event_list	*event;

	if (!list)
		mlxge_log(WARNING, "!! No MLXGE events have been loaded !!");
	while (list)
	{
		layer = (t_layer *)list->layer_ref;
		event = (t_event_list *)layer->event_list[event_type];
		while (event)
		{
			if (event->code == code)
			{
				mlxge_log(DEBUG, "Handling Event....");
				event->handle_event(event->event_param);
			}
			event = event->next;
		}
		list = list->next;
	}
	return (0);
}

int	mlxge_on_keypress_event(int keycode, void *param)
{
	// mlxge_log(DEBUG, "KeyPress - %i", keycode);
	return (handle_events(keycode, (t_event_layer *)param, ON_KEY_PRESS));
}

int	mlxge_on_keyrelease_event(int keycode, void *param)
{
	// (void)param;
	// mlxge_log(DEBUG, "On KeyRelease Event - %i", keycode);
	// if (!events_to_handle(keycode, (t_event_layer *)param, ON_KEY_RELEASE))
	// 	remove_key_input_poll(keycode);
	return (handle_events(keycode, (t_event_layer *)param, ON_KEY_RELEASE));
}

int	mlxge_on_destroy_event(void *param)
{
	// mlxge_log(DEBUG, "!! MLXGE ON DESTROY EVENT !!");
	if (!param)
		param = get_mlxge_core()->event_layer;
	mlxge_destroy_layers(EVENT_LAYER, (t_event_layer *)param);
	return (mlxge_destroy());
}

void	mlxge_set_mlx_event_hooks(void *mlx_win_ptr, t_event_layer *evnt_lst)
{
	int	*event;

	event = mlx_event_codes();
	mlx_hook(mlx_win_ptr, event[ON_KEY_PRESS], 1L<<0, mlxge_on_keypress_event, evnt_lst);
	mlx_hook(mlx_win_ptr, event[ON_KEY_RELEASE], 1L<<1, mlxge_on_keyrelease_event, evnt_lst);
	// mlx_hook(mlx_win_ptr, ON_MOUSE_PRESS, 0, mlxge_on_mouse_event, NULL);
	// mlx_hook(mlx_win_ptr, ON_MOUSE_RELEASE, 0, mlxge_on_mouse_event, NULL);
	// mlx_hook(mlx_win_ptr, ON_MOUSE_MOVE, 0, mlxge_on_mouse_move_event, NULL);
	// mlx_hook(mlx_win_ptr, ON_EXPOSE, 0, mlxge_on_expose_event, NULL);
	mlx_hook(mlx_win_ptr, event[ON_DESTROY], 0L, mlxge_on_destroy_event, evnt_lst);
}

void	*mlxge_load_events_layers(t_layer **layers)
{
	void			*event_layer;
	t_event_layer	*layer;
	t_window_layer	*node;

	event_layer = (void *)0;
	node = *layers;
	while (node)
	{
		layer = new_event_layer();
		layer->layer_ref = node;
		mlxge_push_layer_list_front(EVENT_LAYER, layer, &event_layer);
		node = node->next;
	}
	return (event_layer);
}

void	mlxge_destroy_events(t_event_list **events)
{
	t_event_list		*node;
	enum e_event_type	type;

	type = ON_KEY_PRESS;
	while (type < COUNT_EVENT_TYPES)
	{
		node = events[type];
		while (node)
		{
			events[type] = events[type]->next;
			free(node);
			node = events[type];
		}
		type++;
	}
	free(events);
	events = (void *)0;
}

void	**mlxge_new_event_list(void)
{
	return (ft_calloc(COUNT_EVENT_TYPES, sizeof(t_event_list *)));
}

// ----- API -------------------------------------------------------------------

void	*mlxge_new_key_event(int type, int code, int (*funct)(), void *param)
{
	t_event		*event;

	event = ft_calloc(1, sizeof(t_event));
	if (!event)
	{
		mlxge_log(ERROR, ERR_EVNT_FAIL" : Couldn't allocate memory");
		return (0);
	}
	event->type = type;
	event->code = code;
	event->handle_event = funct;
	event->event_param = param;
	return ((void *)event);
}

void	mlxge_push_event(void *event_ptr, void **event_list_ptr)
{
	t_event			*event;
	t_event_list	*list;

	event = (t_event *)event_ptr;
	list = ((t_event_list **)event_list_ptr)[event->type];
	if (!list)
	{
		((t_event_list **)event_list_ptr)[event->type] = event;
		return ;
	}
	while (list->next)
		list = list->next;
	list->next = event;
}
