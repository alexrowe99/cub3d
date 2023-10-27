/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:03:54 by lmells            #+#    #+#             */
/*   Updated: 2023/10/27 19:27:18 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>

static inline t_mlxge	*new_core(void)
{
	return (ft_calloc(1, sizeof(t_mlxge)));
}

static inline bool	init_core(t_mlxge *core)
{
	core->mlx_inst_ptr = mlx_init();
	if (!core->mlx_inst_ptr)
	{
		mlxge_log(ERROR, "Failed to create new MLXGE core state because : "\
			"Couldn't allocate memory");
		return (false);
	}
	core->sandbox = ft_calloc(1, sizeof(struct s_user_app));
	if (!core->sandbox)
	{
		mlxge_log(ERROR, "Failed to create new MLXGE core state because : "\
			"Couldn't allocate memory");
		return (false);
	}
	return (true);
}

t_mlxge	*get_core(void)
{
	static t_mlxge	*core;

	if (!core)
	{
		core = new_core();
		if (!core)
		{
			mlxge_log(ERROR, "Failed to create new MLXGE core state because : "\
				"Couldn't allocate memory");
			exit(ERROR);
		}
		if (!init_core(core))
		{
			free(core);
			exit(ERROR);
		}
	}
	return (core);
}

static inline double	get_elapsed_secs(struct timeval *s, struct timeval *e)
{
	return ((e->tv_sec - s->tv_sec) + ((e->tv_usec - s->tv_usec) / 1000000.0f));
}

#define ONE_SECOND 1.0f
int	mlxge_on_update(t_layer *list)
{
	t_mlxge	*core;
	t_layer	*layer;

	core = get_core();
	gettimeofday(&core->timer.end, 0);
	core->timer.elapsed_sec = get_elapsed_secs(&core->timer.start,
								&core->timer.end);
	gettimeofday(&core->timer.start, 0);
	core->timer.since_last_print += core->timer.elapsed_sec;
	if (core->timer.since_last_print >= ONE_SECOND)
	{
		printf("\033[A\33[2K\rElapsed: %f | FPS: %i\n",
			core->timer.elapsed_sec,
			(int)(ONE_SECOND/core->timer.elapsed_sec));
		core->timer.since_last_print = 0.0f;
	}
	layer = list;
	while (layer->next)
	{
		layer = layer->next;
		layer->on_update(layer);
	}
	mlxge_render(core->mlx_inst_ptr, core->mlx_window->mlx_win_ptr, list);
	return (1);
}

// ----- API -------------------------------------------------------------------

void	mlxge_init(void *app_struct_ptr,
			int (*destroy_app_struct_funct)(void *))
{
	*get_core()->sandbox = (struct s_user_app){
		.user_app_ref = app_struct_ptr,
		.user_app_destroy = destroy_app_struct_funct
	};
}

#define SUCCESS 0
void	mlxge_destroy(void)
{
	t_mlxge	*core;

	core = get_core();
	if (core->event_layers)
		mlxge_destroy_event_layers(core->event_layers);
	if (core->render_layers)
		mlxge_destroy_layers(core->render_layers);
	if (core->mlx_window && core->mlx_window->mlx_win_ptr)
		mlx_destroy_window(core->mlx_inst_ptr, core->mlx_window->mlx_win_ptr);
	free(core->mlx_window);
	if (core->sandbox && core->sandbox->user_app_ref)
		core->sandbox->user_app_destroy(core->sandbox->user_app_ref);
	free(core->sandbox);
	free(core);
	mlxge_log(INFO, "MLXGE has successfully been destroyed... Exiting!");
	exit(SUCCESS);
}

int	mlxge_run(void)
{
	t_mlxge	*core;

	core = get_core();
	core->event_layers = mlxge_load_event_layers(core->render_layers);
	if (!core->event_layers)
		mlxge_destroy();
	mlxge_load_mlx_event_hooks(core->mlx_window->mlx_win_ptr,
		core->event_layers);
	mlx_loop_hook(core->mlx_inst_ptr, mlxge_on_update, core->render_layers);
	core->timer = (t_gtime){{0}, {0}, 0.0f, 0.0f};
	gettimeofday(&core->timer.start, 0);
	return (mlx_loop(core->mlx_inst_ptr));
}
