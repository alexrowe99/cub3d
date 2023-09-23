/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:06:51 by lmells            #+#    #+#             */
/*   Updated: 2023/09/23 15:19:39 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <core.h>
#include <layers.h>
#include <events.h>

// ----- Core ------------------------------------------------------------------

t_core	*get_engine(void)
{
	static t_core	engine;

	return (&engine);
}

bool	engine_error(const char *message)
{
	ft_printf("\e[0;91m[Engine Fatal Error]\e[0m: %s.\n", message);
	return (false);
}

void	engine_warning(const char *message)
{
	ft_printf("\e[0;93m[Engine Warning]\e[0m: %s.\n", message);
}

void	engine_info(const char *message)
{
	ft_printf("\e[0;92m[Engine Info]\e[0m: %s.\n", message);
}

void	engine_debug(const char *message)
{
	ft_printf("\e[0;96m[Engine Debug]\e[0m: %s.\n", message);
}

static t_mlx_inst	*create_new_mlx_instance(size_t width, size_t height,
						char *title)
{
	bool		init;
	t_mlx_inst	*mlx;

	init = true;
	mlx = ft_calloc(1, sizeof(t_mlx_inst));
	if (!mlx)
	{
		perror(FATAL_ERROR);
		return (NULL);
	}
	mlx->inst = mlx_init();
	if (!mlx->inst)
		init = engine_error("Could not initialise mlx pointer");
	mlx->win = mlx_new_window(mlx->inst, width, height, (char *)title);
	if (!mlx->win)
		init = engine_error("Could not initialise win pointer");
	if (!init)
		return (ft_vfree(1, &mlx));
	return (mlx);
}

static t_img	*create_mlx_window_image(void *mlx_inst, size_t width,
					size_t height)
{
	t_img	*image;

	image = (t_img *)ft_calloc(1, sizeof(t_img));
	if (!image)
	{
		perror(FATAL_ERROR);
		return (NULL);
	}
	image->dim = v2i(width, height);
	image->mlx_img_ptr = mlx_new_image(mlx_inst, width, height);
	if (!image->mlx_img_ptr)
	{
		engine_error("MiniLibX could not create a new image");
		return (ft_vfree(1, &image));
	}
	image->pbuff = (uint32_t *)mlx_get_data_addr(image->mlx_img_ptr,
					&image->pctx[0], &image->pctx[1], &image->pctx[2]);
	return (image);
}

static bool	create_mlx_window(size_t width, size_t height)
{
	errno = 0;

	// ----- Initialise Window Layer -------------------------------------------
	
	t_layer	*window_layer = engine_new_layer();
	if (!window_layer)
	{
		perror(FATAL_ERROR);
		return (false);
	}
	window_layer->is_window_layer = true;

	// -------------------------------------------------------------------------
	
	// ----- Initialise Window Layer Destroy Events ----------------------------

	t_destroy_event	*destroy_event = engine_new_destroy_event();
	if (!destroy_event)
	{
		perror(FATAL_ERROR);
		engine_destroy_layer(window_layer);
		return (false);
	}
	engine_push_event_list_back(destroy_event, window_layer->events);

	#define KEY_ESC 53
	t_key_event	*close_event = engine_new_keypress_event(KEY_ESC,
								engine_destroy, NULL);
	if (!close_event)
	{
		perror(FATAL_ERROR);
		engine_destroy_layer(window_layer);
		return (false);
	}
	engine_push_event_list_back(close_event, window_layer->events);

	// ----- Push Window Layer to render queue ---------------------------------

	if (engine_push_layer_list(window_layer, &get_engine()->render_layers) < 0)
	{
		engine_destroy_layer(window_layer);
		return (engine_error("Failed to initialise application layers"));
	}
	
	// -------------------------------------------------------------------------
	
	// ----- Create Window Layer Image -----------------------------------------
	
	window_layer->image = create_mlx_window_image(get_engine()->mlx->inst,
							width, height);
	if (!window_layer->image)
	{
		engine_destroy_layer(window_layer);
		return (false);
	}
	get_engine()->mlx->win_img = window_layer->image->mlx_img_ptr;

	// -------------------------------------------------------------------------
	return (true);
}

static void	load_mlx_event_hooks(t_layer_list *event_layers, void *mlx_win)
{
	size_t			i;
	t_layer_list	*layer_node;
	t_event_list	*event_node;

	if (!event_layers)
		engine_warning("No MiniLibX event hooks avaliable to load");
	layer_node = event_layers;
	while (layer_node)
	{
		i = 0;
		while (i < COUNT_SUPPORTED_EVENTS)
		{
			if (layer_node->layer->events[i])
			{
				event_node = layer_node->layer->events[i];
				while (event_node)
				{
					mlx_hook(mlx_win, event_node->event.type, 0,
						event_node->event.handler, event_layers);
					event_node = event_node->next;
				}
			}
			i++;
		}
		layer_node = layer_node->next;
	}
}

int	engine_handle_keypress(int keycode, void *event_layers_ptr)
{
	t_event			*event;
	t_event_list	*event_node;
	t_layer_list	*event_list;

	char *dbg = NULL;
	ft_asprintf(&dbg, "KEYPRESS EVENT - keycode = %i", keycode);
	engine_debug(dbg);
	free(dbg);

	event_list = (t_layer_list *)event_layers_ptr;
	while (event_list)
	{
		event_node = event_list->layer->events[KEY_PRESS_EVENT];
		while (event_node)
		{
			event = &event_node->event;
			if (event->code == keycode)
			{
				event->handled = true;
				return (event->key_event_action(event->param));
			}
			event_node = event_node->next;
		}
		event_list = event_list->next;
	}
	return (keycode);
}

static bool	event_in_bounds(t_v2i *bounds, int x, int y)
{
	return (bounds[BOUNDS_START_POS].x <= x && x < bounds[BOUNDS_END_POS].x
		&& bounds[BOUNDS_START_POS].y <= y && y < bounds[BOUNDS_END_POS].y);
}

int	engine_handle_mouse_event(int code, int x, int y, void *event_layers_ptr)
{
	t_event			*event;
	t_event_list	*event_node;
	t_layer_list	*event_list;

	char *dbg = NULL;
	ft_asprintf(&dbg, "MOUSE PRESS EVENT - code = %i", code);
	engine_debug(dbg);
	free(dbg);

	event_list = (t_layer_list *)event_layers_ptr;
	while (event_list)
	{
		event_node = event_list->layer->events[MOUSE_PRESS_EVENT];
		while (event_node)
		{
			event = &event_node->event;
			if (event_in_bounds(event->bounds, x, y) && event->code == code)
			{
				event->handled = true;
				return (event->mouse_event_action(code, event->param));
			}
			event_node = event_node->next;
		}
		event_list = event_list->next;
	}
	return (code);
}

// ----- API -------------------------------------------------------------------

int	engine_init(size_t width, size_t height, const char *title)
{
	t_core	*engine;

	engine_info("Initialising engine..");
	engine = get_engine();
	
	engine->mlx = create_new_mlx_instance(width, height, (char *)title);
	if (!engine->mlx || !create_mlx_window(width, height))
		return (-1);
	engine_info("MiniLibX application window has been initialised");

	return (0);
}

void	engine_bind_application(void *application_ptr,
			int (*destructor)(void *), int (*update_loop)(void *))
{
	t_core	*core;

	engine_info("Binding sandbox application references..");
	if (!application_ptr)
		engine_warning("Application pointer is a NULL reference");
	if (!destructor)
		engine_warning("Application destructor is a NULL reference");
	if (!update_loop)
		engine_warning("Application update loop is a NULL reference");
	core = get_engine();
	core->app_ref = application_ptr;
	core->app_dtor = destructor;
	core->app_update = update_loop;
	if (core->app_update)
	{
		engine_debug("Binding run loop to MiniLibX instance");
		mlx_loop_hook(core->mlx->inst, core->app_update, core->app_ref);
	}
}

static void	push_event_layers_front(t_layer_list *node,
				t_layer_list **layer_list_head)
{
	t_layer_list	*current;

	if (!*layer_list_head)
	{
		*layer_list_head = node;
		return ;
	}
	current = *layer_list_head;
	node->next = current;
	*layer_list_head = node;
}

static t_layer_list	*copy_layer_node(t_layer_list *layer_node)
{
	t_layer			*layer;
	t_layer_list	*dup_layer_node;

	dup_layer_node = engine_new_layer_list_node();
	if (!dup_layer_node)
		return (NULL);
	dup_layer_node->layer = engine_new_layer();
	if (!dup_layer_node)
		return (ft_vfree(1, &dup_layer_node));
	layer = layer_node->layer;
	*dup_layer_node->layer = (t_layer){
							.events[DESTROY_EVENT]=layer->events[DESTROY_EVENT],
							.events[KEY_PRESS_EVENT]=layer->events[KEY_PRESS_EVENT],
							.events[MOUSE_PRESS_EVENT]=layer->events[MOUSE_PRESS_EVENT],
							.image=layer->image,
							.is_window_layer=layer->is_window_layer};
	dup_layer_node->next = NULL;
	return (dup_layer_node);
}

static t_layer_list	*load_event_layers(t_layer_list *layers)
{
	t_layer_list	*layer_node;
	t_layer_list	*event_layers;
	t_layer_list	*dup_node_no_next;

	errno = 0;
	layer_node = layers;
	event_layers = get_engine()->event_layers;
	while (layer_node)
	{
		dup_node_no_next = copy_layer_node(layer_node);
		if (!dup_node_no_next)
		{
			perror(FATAL_ERROR);
			engine_destroy();
			return (NULL);
		}
		push_event_layers_front(dup_node_no_next, &event_layers);
		layer_node = layer_node->next;
	}
	return (event_layers);
}

int	engine_start_application(void)
{
	t_core	*engine;

	engine = get_engine();
	
	engine_debug("Loading events..");
	engine->event_layers = load_event_layers(engine->render_layers);
	load_mlx_event_hooks(engine->event_layers, engine->mlx->win);

	engine->mlx->running = true;
	engine_info("Starting MiniLibX application..");	
	return (mlx_loop(engine->mlx->inst));
}

int	engine_destroy(void)
{
	t_core	*engine;

	engine_info("Closing MiniLibx application..");
	engine = get_engine();
	if (engine->mlx->running)
	{
		engine_debug("Destroying MiniLibX window image");
		mlx_destroy_image(engine->mlx->inst, engine->mlx->win_img);
		engine->mlx->running = false;
	}
	if (engine->mlx->win)
	{
		engine_debug("Destroying MiniLibX window");
		mlx_destroy_window(engine->mlx->inst, engine->mlx->win);
	}

	engine_debug("Destroying engine layers");
	engine_destroy_layer_list(&engine->render_layers);
	
	engine_debug("Destorying application data");
	if (!engine->app_dtor)
	{
		engine_warning("No application destructor was bound");
		engine_warning("Exiting abruptly..");
		exit(1);
	}
	exit(engine->app_dtor(engine->app_ref));
	return (0);
}
