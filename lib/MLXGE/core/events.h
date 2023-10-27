/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:42:57 by lmells            #+#    #+#             */
/*   Updated: 2023/10/25 17:16:07 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

enum e_key_input_types
{
	PRESS = 0,
	RELEASE = 1
};

enum e_event_types
{
	KEY_PRESS,
	KEY_RELEASE,
	// MOUSE_PRESS,
	// MOUSE_RELEASE,
	// MOUSE_MOVE,
	DESTROY,
	COUNT_EVENT_TYPES
};

enum e_mlx_event_codes
{
	ON_KEY_PRESS_EVENT = 2,
	ON_KEY_RELEASE_EVENT = 3,
	// ON_MOUSE_PRESS_EVENT = ,
	// ON_MOUSE_RELEASE_EVENT = ,
	// ON_MOUSE_MOVE_EVENT = ,
	ON_DESTROY_EVENT = 17
};

typedef struct s_event_list
{
	int					type;
	int					code;
	int					(*handler)(int, void *);
	int					(*action)(void *);
	void				*param;
	struct s_event_list	*next;
}	t_event;

t_event	*mlxge_new_key_event(enum e_key_input_types input, int keycode,
			int (*action_func)(void *param), void *param);
void	mlxge_push_event(t_event *event, t_event **list);
void	mlxge_destroy_events(t_event *list);

#endif
