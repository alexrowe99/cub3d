/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:33:54 by lmells            #+#    #+#             */
/*   Updated: 2023/12/18 12:30:31 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <layers.h>

#define ERR_LAY_CREAT "Failed to create a new MLXGE layer because"

static inline t_layer	*new_layer(void)
{
	t_layer	*layer;

	layer = ft_calloc(1, sizeof(t_layer));
	if (!layer)
		mlxge_log(ERROR, ERR_LAY_CREAT" : Couldn't allocate memory");
	return (layer);
}

t_layer	*create_window_layer(t_dimensions size)
{
	t_v2d	origin;
	t_layer	*win_layer;

	win_layer = new_layer();
	if (!win_layer)
		return ((void *)0);
	origin = (t_v2d){0, 0};
	win_layer->frame = mlxge_new_frame(origin, size, true);
	if (!win_layer->frame)
	{
		mlxge_log(ERROR, ERR_LAY_CREAT" : Couldn't create MLXGE frame");
		free(win_layer);
		win_layer = (void *)0;
	}
	return (win_layer);
}

// ----- API -------------------------------------------------------------------

/*
	Allocates a new layer on the heap.
	Binds on_update function pointer to the layer. This funcion will be called during the applications update loop.
	Creates the render frame to draw the layer's images to. (Like a static background image and dynamic foreground e.g. raycast walls)
*/
// Create a new layer. Returns NULL on error.
t_layer	*mlxge_new_layer(t_v2d origin, t_dimensions size,
			int (*on_update)(t_layer *, double))
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
		layer = (void *)0;
	}
	return (layer);
}

// Push layer to back of render queue.
int	mlxge_push_layer(t_layer *layer)
{
	t_layer	*node;
	t_layer	**list;

	list = &get_core()->render_layers;
	node = *list;
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = layer;
	}
	else
		*list = layer;
	return (1);
}
