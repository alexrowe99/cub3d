/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:42:57 by lmells            #+#    #+#             */
/*   Updated: 2023/10/30 15:10:11 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

enum e_key_input_types
{
	PRESS = 0,
	RELEASE = 1
};

// MOUSE_PRESS = 3,
// MOUSE_RELEASE,
// MOUSE_MOVE,
enum e_event_types
{
	KEY_PRESS,
	KEY_RELEASE,
	DESTROY,
	COUNT_EVENT_TYPES
};

// ON_MOUSE_PRESS_EVENT = ??, (Look at harms-smits mlx docs)
// ON_MOUSE_RELEASE_EVENT = ,
// ON_MOUSE_MOVE_EVENT = ,
enum e_mlx_event_codes
{
	ON_KEY_PRESS_EVENT = 2,
	ON_KEY_RELEASE_EVENT = 3,
	ON_DESTROY_EVENT = 17
};

typedef struct s_event_list
{
	int					type;
	int					code;
	int					(*handler)(void *);
	void				*param;
	struct s_event_list	*next;
}	t_event;

void	mlxge_push_event(t_event *event, t_event **list);
void	mlxge_destroy_events(t_event *list);

t_event	*mlxge_new_key_event(enum e_key_input_types input, int keycode,
			int (*handler_func)(void *param), void *param);
t_event	*mlxge_new_destroy_event(int (*handler_funct)(void *), void *param);

#endif
