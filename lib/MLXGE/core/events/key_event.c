/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 20:48:48 by lmells            #+#    #+#             */
/*   Updated: 2023/11/09 11:48:49 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <events.h>
#include <core.h>

int	mlxge_handle_key_events(enum e_event_types type, int keycode,
						t_event_layer *layers_list)
{
	t_event			*event;
	t_event_layer	*layers;

	layers = layers_list;
	while (layers)
	{
		event = layers->layer_ref->events[type];
		while (event)
		{
			if (event->code == keycode)
			{
				event->handler(event->param);
				return (1);
			}
			event = event->next;
		}
		layers = layers->next;
	}
	return (0);
}

int	mlxge_handle_key_press_events(int keycode, t_event_layer *list)
{
	int			i;
	t_key_input	*keyboard;

	if (mlxge_handle_key_events(KEY_PRESS, keycode, list))
		return (1);
	i = 0;
	keyboard = mlxge_keyboard();
	while (i < COUNT_TRACKED_KEYCODES && keyboard->input[i].code != keycode)
		i++;
	keyboard->input[i].is_down = true;
	return (keycode);
}

int	mlxge_handle_key_release_events(int keycode, t_event_layer *list)
{
	int			i;
	t_key_input	*keyboard;

	if (mlxge_handle_key_events(KEY_RELEASE, keycode, list))
		return (1);
	i = 0;
	keyboard = mlxge_keyboard();
	while (i < COUNT_TRACKED_KEYCODES && keyboard->input[i].code != keycode)
		i++;
	keyboard->input[i].is_down = false;
	return (keycode);
}

// ---- API --------------------------------------------------------------------

t_event	*mlxge_new_key_event(enum e_key_input_types input, int keycode,
			int (*handler_func)(void *param), void *param)
{
	t_event		*event;

	event = ft_calloc(1, sizeof(t_event));
	if (!event)
	{
		mlxge_log(ERROR, "Failed to create new MLXGE key event because : "\
			"Couldn't allocate memory");
		return ((void *)0);
	}
	event->type = input;
	event->code = keycode;
	event->handler = handler_func;
	event->param = param;
	return (event);
}
