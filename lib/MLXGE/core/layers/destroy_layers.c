/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_layers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:15:15 by lmells            #+#    #+#             */
/*   Updated: 2023/12/26 13:13:38 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <layers.h>
#include <render/render_core.h>
#include <stdio.h>

inline static void	destroy_layer_events(t_layer *layer)
{
	int	i;

	i = -1;
	while (++i < COUNT_EVENT_TYPES)
		mlxge_destroy_events(layer->events[i]);
}

inline static void	destroy_layer_images(t_layer *layer)
{
	if (layer->z_buffer_tree)
		destroy_z_buffer_tree(layer->z_buffer_tree);
	if (layer->frame)
		mlxge_destroy_image(layer->frame);
}

void	mlxge_destroy_layers(t_layer *list)
{
	t_layer		*node;

	node = list;
	while (node)
	{
		list = list->next;
		destroy_layer_events(node);
		destroy_layer_images(node);
		mlxge_destroy_viewports(node->viewport_list);
		free(node);
		node = list;
	}
}
