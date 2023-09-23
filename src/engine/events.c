/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:51:58 by lmells            #+#    #+#             */
/*   Updated: 2023/09/23 13:52:39 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <events.h>
#include <libftall.h>

t_destroy_event	*engine_new_destroy_event(void)
{
	t_destroy_event	*event_node;

	event_node = (t_destroy_event *)ft_calloc(1, sizeof(t_destroy_event));
	if (event_node)
	{
		event_node->event = (t_event){.type=ON_DESTROY_EVENT, .code=0,
							.bounds[BOUNDS_START_POS]=v2i(0, 0),
							.bounds[BOUNDS_END_POS]=v2i(0, 0),
							.handler=engine_destroy,
							.key_event_action=NULL, .mouse_event_action=NULL,
							.param=NULL, .handled=false};
		event_node->next = NULL;	
	}
	return (event_node);
}

t_v2i	*engine_set_event_bounds(t_v2i orig, t_v2i size)
{
	t_v2i	*event_bounds;

	event_bounds = ft_calloc(2, sizeof(t_v2i));
	if (event_bounds)
	{
		event_bounds[BOUNDS_START_POS] = orig;
		event_bounds[BOUNDS_END_POS] = v2i_sum(orig, size);
	}
	return (event_bounds);
}

t_key_event	*engine_new_keypress_event(int keycode, int (*func)(), void *param)
{
	t_key_event	*event_node;

	event_node = (t_key_event *)ft_calloc(1, sizeof(t_key_event));
	if (event_node)
	{
		event_node->event = (t_event){.type=ON_KEY_PRESS_EVENT, .code=keycode,
							.bounds[BOUNDS_START_POS]=v2i(0, 0),
							.bounds[BOUNDS_END_POS]=v2i(0, 0),
							.handler=engine_handle_keypress,
							.key_event_action=func, .param=param,
							.mouse_event_action=NULL, .handled=false};
		event_node->next = NULL;
	}
	return (event_node);
}

t_mouse_event	*engine_new_mousepress_event(int code, t_v2i *bounds,
					int (*event_action)(int button, void *param), void *param)
{
	t_mouse_event	*event_node;

	event_node = NULL;
	if (bounds)
	{
		event_node = (t_mouse_event *)ft_calloc(1, sizeof(t_mouse_event));
		if (event_node)
		{
			event_node->event = (t_event){.type=ON_MOUSE_PRESS_EVENT, .code=code,
								.bounds[BOUNDS_START_POS]=bounds[BOUNDS_START_POS],
								.bounds[BOUNDS_END_POS]=bounds[BOUNDS_END_POS],
								.handler=engine_handle_mouse_event,
								.mouse_event_action=event_action, .param=param,
								.key_event_action=NULL, .handled=false};
			event_node->next = NULL;
		}
		free(bounds);
	}
	return (event_node);
}

void	destroy_event_list(t_event_list **head)
{
	t_event_list	*current;
	// t_v2i			**b;

	current = *head;
	while (current)
	{
		*head = current->next;
		// if (current->event.bounds)
		// {
		// 	b = current->event.bounds;
		// 	b[BOUNDS_END_POS]->x
		// }
		// 	ft_vfree(3, &current->event.bounds[BOUNDS_START_POS],
		// 		&current->event.bounds[BOUNDS_START_POS], &current->event.bounds);
		free(current);
		current = *head;
	}
}

static size_t	event_index(size_t event_type)
{
	if (event_type == ON_DESTROY_EVENT)
		return (DESTROY_EVENT);
	if (event_type == ON_KEY_PRESS_EVENT)
		return (KEY_PRESS_EVENT);
	// if (event_type == ON_KEY_RELEASE_EVENT)
	// 	return (KEY_RELEASE_EVENT);
	if (event_type == ON_MOUSE_PRESS_EVENT)
		return (MOUSE_PRESS_EVENT);
	return (COUNT_SUPPORTED_EVENTS);
}

void	engine_push_event_list_back(t_event_list *event_node,
			t_event_list **list)
{
	size_t			i;
	t_event_list	*current;

	i = event_index(event_node->event.type);
	if (!list[i])
	{
		list[i] = event_node;
		return ;
	}
	current = list[i];
	while (current->next)
		current = current->next;
	current->next = event_node;
}
