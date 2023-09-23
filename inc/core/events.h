/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:13:19 by lmells            #+#    #+#             */
/*   Updated: 2023/09/23 13:33:55 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include <vector.h>
# include <stdbool.h>

enum e_supported_event_types
{
	DESTROY_EVENT,
	KEY_PRESS_EVENT,
	// KEY_RELEASE_EVENT,
	MOUSE_PRESS_EVENT,
	COUNT_SUPPORTED_EVENTS
};

# define ON_DESTROY_EVENT 17
# define ON_KEY_PRESS_EVENT 2
# define ON_KEY_RELEASE_EVENT 3
# define ON_MOUSE_PRESS_EVENT 4

enum e_supported_mouse_click
{
	LEFT_CLICK = 1,
	RIGHT_CLICK,
	MIDDLE_CLICK,
	SCROLL_UP,
	SCROLL_DOWN
};

# define BOUNDS_START_POS 0
# define BOUNDS_END_POS 1
# define COUNT_BOUNDS 2

typedef struct s_event_handler
{
	int					type;
	int					code;
	t_v2i				bounds[COUNT_BOUNDS];
	int					(*handler)();
	int					(*key_event_action)(void *);
	int					(*mouse_event_action)(int, void *);
	void				*param;
	bool				handled;
}	t_event;

typedef struct s_event_list
{
	t_event				event;
	struct s_event_list	*next;
}	t_event_list;

typedef t_event_list	t_key_event;
typedef t_event_list	t_mouse_event;
typedef t_event_list	t_destroy_event;

void			destroy_event_list(t_event_list **head);
void			engine_push_event_list_back(t_event_list *event_node,
					t_event_list **list);
t_key_event		*engine_new_keypress_event(int keycode, int (*func)(),
					void *param);
t_destroy_event	*engine_new_destroy_event(void);


#endif
