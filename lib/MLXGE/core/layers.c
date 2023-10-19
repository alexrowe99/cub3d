/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:01:00 by lmells            #+#    #+#             */
/*   Updated: 2023/10/19 17:48:37 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>

static void 	push_event_layer_list_front(t_event_layer *layer, t_event_layer **list)
{
	t_event_layer	*head;

	head = *list;
	if (head)
		layer->next = head;
	*list = layer;
}

static void 	push_window_layer_list_front(t_window_layer *layer, t_window_layer **list)
{
	t_window_layer	*head;

	head = *list;
	if (head)
		layer->next = head;
	*list = layer;
}

void	mlxge_destroy_layers(t_list_type type, void *layers)
{
	t_window_layer	*wlist[2];
	t_event_layer	*elist[2];

	if (type == EVENT_LAYER)
	{
		elist[0] = (t_event_layer *)layers;
		while (elist[0])
		{
			elist[1] = elist[0]->next;
			free(elist[0]);
			elist[0] = elist[1];
		}
		return ;
	}
	wlist[0] = (t_window_layer *)layers;
	while (wlist[0])
	{
		wlist[1] = wlist[0]->next;
		if (wlist[0]->event_list)
			mlxge_destroy_events((t_event_list **)wlist[0]->event_list);
		if (wlist[0]->image_list)
		{
			mlxge_log(DEBUG, "Destroying layer's image list");
			mlxge_destroy_images(wlist[0]->image_list);
		}
		if (wlist[0]->frame)
		{
			mlxge_log(DEBUG, "Destroying layer's frame");
			mlxge_destroy_images(wlist[0]->frame);
		}
		free(wlist[0]);
		wlist[0] = wlist[1];
	}
}

static void	*mlxge_create_new_layer(int frame_width, int frame_height, void *on_update,
			void *mlx_img_ptr)
{
	t_layer	*layer;

	layer = malloc(1 * sizeof(t_layer));
	if (layer)
	{
		*layer = (t_layer){
			.frame = mlxge_new_frame(0, 0, frame_width, frame_height, mlx_img_ptr),
			.event_list = mlxge_new_event_list(),
			.on_update = (t_on_update)on_update,
			.image_list = (void *)0,
			.viewport = (void *)0,
			.next = (void *)0,
		};
		if (!layer->event_list)
		{
			mlxge_log(ERROR, ERR_LAYER_FAIL" : Couldn't allocate memory for "\
					"the layer's event list");
			free(layer);
			layer = (void *)0;
		}
	}
	return ((void *)layer);
}

void	*mlxge_window_layer(void *on_update, void *mlx_img_ptr)
{
	t_dimensions	win;

	win = get_mlxge_core()->win->dim;
	return (mlxge_create_new_layer(win.width, win.height, on_update,
		mlx_img_ptr));
}

void	mlxge_push_layer_list_front(t_list_type type, void *layer, void **list)
{
	if (type == EVENT_LAYER)
		return (push_event_layer_list_front((t_event_layer *)layer,
				(t_event_layer **)list));
	if (type == WINDOW_LAYER)
		return (push_window_layer_list_front((t_window_layer *)layer,
				(t_window_layer **)list));
}

// ----- API -------------------------------------------------------------------

// Pass -frame_width & -frame_height to set the size to match the window
void	*mlxge_new_layer(int frame_width, int frame_height, void *on_update)
{
	if (frame_width < 0)
		frame_width = get_mlxge_core()->win->dim.width;
	if (frame_height < 0)
		frame_height = get_mlxge_core()->win->dim.height;
	return (mlxge_create_new_layer(frame_width, frame_height, on_update,
			(void *)0));
}

void	mlxge_push_layer(t_layer *layer)
{
	t_layer	**layer_list;

	layer_list = (t_layer **)&get_mlxge_core()->layers;
	if (!*layer_list)
	{
		*layer_list = layer;
		return ;
	}
	while ((*layer_list)->next)
		*layer_list = (*layer_list)->next;
	(*layer_list)->next = layer;
}
