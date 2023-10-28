/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:33:54 by lmells            #+#    #+#             */
/*   Updated: 2023/10/28 21:27:16 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <layers.h>

#define ERR_LAY_CREAT "Failed to create a new MLXGE layer because"

void	mlxge_destroy_layers(t_layer *list)
{
	int			i;
	t_layer		*node;
	t_img_quad	*image;

	node = list;
	while (node)
	{
		list = list->next;
		i = -1;
		while (++i < COUNT_EVENT_TYPES)
			mlxge_destroy_events(node->events[i]);
		while (node->images_to_render)
		{
			image = node->images_to_render;
			node->images_to_render = node->images_to_render->next;
			mlxge_destroy_image_quad(image);
		}
		if (node->viewport_list)
			mlxge_destroy_viewports(node->viewport_list);
		if (node->frame)
			mlxge_destroy_image_quad(node->frame);
		free(node);
		node = list;
	}
}

static inline t_layer	*new_layer(void)
{
	t_layer	*layer;

	layer = ft_calloc(1, sizeof(t_layer));
	if (!layer)
	{
		mlxge_log(ERROR, ERR_LAY_CREAT" : Couldn't allocate memory");
		return ((void *)0);
	}
	return (layer);
}

t_layer	*create_window_layer(t_dimensions size)
{
	t_v2i	origin;
	t_layer	*win_layer;

	win_layer = new_layer();
	if (!win_layer)
		return ((void *)0);
	origin = (t_v2i){0, 0};
	win_layer->frame = mlxge_new_frame(origin, size, true);
	if (!win_layer->frame)
	{
		mlxge_log(ERROR, ERR_LAY_CREAT" : Couldn't create MLXGE frame");
		free(win_layer);
		return ((void *)0);
	}
	return (win_layer);
}

// ----- API -------------------------------------------------------------------

t_layer	*mlxge_new_layer(t_v2i origin, t_dimensions size,
			int (*on_update)(t_layer *))
{
	t_layer	*layer;

	layer = new_layer();
	if (!layer)
		return ((void *)0);
	layer->on_update = on_update;
	layer->frame = mlxge_new_frame(origin, size, false);
	if (!layer->frame)
	{
		mlxge_log(ERROR, ERR_LAY_CREAT" : Couldn't create MLXGE frame");
		free(layer);
		return ((void *)0);
	}
	return (layer);
}

int	mlxge_push_layer(t_layer *layer)
{
	t_layer	*node;
	t_layer	**list;

	list = &get_core()->render_layers;
	node = *list;
	if (!node)
	{
		*list = layer;
		return (1);
	}
	while (node->next)
		node = node->next;
	node->next = layer;
	return (1);
}
