/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:39:11 by lmells            #+#    #+#             */
/*   Updated: 2023/10/19 14:22:07 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>

static void	core_init_mlx(struct s_mlxge *core)
{
	core->mlx = mlx_init();
	if (!core->mlx)
	{
		mlxge_log(ERROR, ERR_FAIL_INIT" : Could not initialise MiniLibX");
		free(core);
		exit(1);
	}
	/* 
		Seems to be a bug with the API - Modified mlx window constructor to setKeyRepeat:0 (OFF)
		mlx_do_key_autorepeatoff(core->mlx);
 	*/
}

struct s_mlxge	*get_mlxge_core(void)
{
	static struct s_mlxge	*core;

	if (!core)
	{
		core = ft_calloc(1, sizeof(struct s_mlxge));
		if (!core)
		{
			mlxge_log(ERROR, ERR_FAIL_INIT" : Cannot allocate memory");
			exit(1);
		}
		core_init_mlx(core);
	}
	return (core);
}

#include <time.h>

struct s_mlxge_clock
{
	clock_t	now;
	double	last_frame_time;
	double	timestep_sec;
};

struct s_mlxge_clock	g_clock;

// #include <stdio.h>
int	mlxge_update(void)
{
	t_layer	**layers_list;
	t_layer	*layers;

	g_clock.now = clock();
	g_clock.timestep_sec = ((double)(g_clock.now)/CLOCKS_PER_SEC) - g_clock.last_frame_time;
	g_clock.last_frame_time = (double)(g_clock.now)/CLOCKS_PER_SEC;

	// printf("Delta Seconds: %f\n", g_clock.timestep_sec);

	// while (g_clock.timestep_sec < target)
	// {
		layers_list = &((t_layer *)get_mlxge_core()->layers)->next;
		layers = *layers_list;
		while (layers)
		{
			layers->on_update(layers, g_clock.timestep_sec);
			layers = layers->next;
		}
	// 	g_clock.timestep_sec -= delta_time;
	// }
	mlxge_render(*layers_list);

	return (0);
}

// ----- API -------------------------------------------------------------------

// Exits the program if initialisation fails.
#define ERR_BIND_APP "Failed to bind application because"
void	mlxge_init(void *app_ptr, int (*app_destructor)(void *app_ptr))
{
	struct s_mlxge	*core;

	mlxge_log(INFO, "Initialising MLXGE...");
	core = get_mlxge_core();
	if (!app_ptr || !app_destructor)
	{
		if (!app_ptr)
			mlxge_log(ERROR, ERR_BIND_APP" : application pointer is NULL reference");
		if (!app_destructor)
			mlxge_log(ERROR, ERR_BIND_APP" : application destructor is NULL reference");
		mlxge_log(WARNING, "Heap memory allocated by application may cause leaks...");
	}
	if (app_ptr)
		core->app_ptr = app_ptr;
	if (app_destructor)
		core->app_destructor = app_destructor;
}

int	mlxge_run(void)
{
	mlxge_log(INFO, "Starting MLXGE application...");

	struct s_mlxge	*core = get_mlxge_core();
	
	mlxge_log(DEBUG, "Binding MiniLibX update loop to run MLXGE window on update");
	mlx_loop_hook(core->mlx, ((t_layer *)core->layers)->on_update, 0);
	mlxge_log(INFO, "Loading MLXGE events...");
	core->event_layer = mlxge_load_events_layers((t_layer **)&core->layers);
	if (!core->event_layer)
	{
		mlxge_log(ERROR, "Failed to start MLXGE application because : "\
			"Couldn't load MLXGE events");
		return (mlxge_destroy());
	}
	mlxge_set_mlx_event_hooks(core->win->id_ptr, core->event_layer);
	return (mlx_loop(core->mlx));
}

int	mlxge_destroy(void)
{
	struct s_mlxge	*core;

	core = get_mlxge_core();
	mlxge_log(DEBUG, "Destroying MLXGE Window...");
	if (core->win)
	{
		if (core->layers && ((t_layer *)core->layers)->next)
			mlxge_destroy_layers(WINDOW_LAYER, ((t_layer *)core->layers)->next);
		mlxge_destroy_window(core->mlx, core->win);
	}
	mlxge_log(DEBUG, "Destroying application...");
	if (core->app_destructor)
		core->app_destructor(core->app_ptr);
	free(core);
	mlxge_log(DEBUG, "MLXGE destroy success!");
	mlxge_log(INFO, "Exiting!");
	exit(0);
	return (0);
}
