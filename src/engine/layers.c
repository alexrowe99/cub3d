/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:04:42 by lmells            #+#    #+#             */
/*   Updated: 2023/09/23 12:38:58 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <layers.h>
#include <stdbool.h>
#include <errno.h>

t_layer	*engine_new_layer(void)
{
	return ((t_layer *)ft_calloc(1, sizeof(t_layer)));
}

t_layer_list	*engine_new_layer_list_node(void)
{
	return ((t_layer_list *)ft_calloc(1, sizeof(t_layer_list)));
}

int	engine_push_layer_list(t_layer *layer, t_layer_list **list)
{
	t_layer_list	*node;
	t_layer_list	*current;

	node = engine_new_layer_list_node();
	if (!node)
	{
		perror(FATAL_ERROR);
		return (-1);
	}
	node->layer = layer;
	if (*list)
	{
		current = *list;
		while (current->next)
			current = current->next;
		current->next = node;
		return (0);
	}
	*list = node;
	return (0);
}

void	engine_destroy_layer(t_layer *layer)
{
	size_t	i;

	if (layer->image)
	{
		if (!layer->is_window_layer)
			free(layer->image->pbuff);
		free(layer->image);
	}
	i = 0;
	while (i < COUNT_SUPPORTED_EVENTS)
	{
		if (layer->events[i])
			destroy_event_list(&layer->events[i]);
		i++;
	}
	free(layer);
}

void	engine_destroy_layer_list(t_layer_list **list)
{
	t_layer_list	*node;

	node = *list;
	while (node)
	{
		*list = node->next;
		if (node->layer)
			engine_destroy_layer(node->layer);
		free(node);
		node = *list;
	}
}

t_layer_list	*engine_get_render_layers_list(void)
{
	return (get_engine()->render_layers);
}

t_layer_list	*engine_get_event_layers_list(void)
{
	return (get_engine()->event_layers);
}
