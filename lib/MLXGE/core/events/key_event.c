/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 20:48:48 by lmells            #+#    #+#             */
/*   Updated: 2023/10/27 21:04:16 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <events.h>
#include <core.h>

static int	mlxge_handle_key_press(int keycode, void *param)
{
	return (mlxge_handle_event(keycode, (t_event_layer *)param, KEY_PRESS));
}

static int	mlxge_handle_key_release(int keycode, void *param)
{
	return (mlxge_handle_event(keycode, (t_event_layer *)param, KEY_RELEASE));
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
