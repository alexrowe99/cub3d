/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 20:39:42 by lmells            #+#    #+#             */
/*   Updated: 2023/11/02 15:33:45 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>

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
	// if (core->timer.since_last_print >= ONE_SECOND)
	// {
	// 	printf("\033[A\33[2K\rElapsed: %f | FPS: %i\n",
	// 		core->timer.elapsed_sec,
	// 		(int)(ONE_SECOND / core->timer.elapsed_sec));
	// 	core->timer.since_last_print = 0.0f;
	// }
	layer = list;
	while (layer->next)
	{
		layer = layer->next;
		layer->on_update(layer);
	}
	mlxge_render(core->mlx_inst_ptr, core->mlx_window->mlx_win_ptr, list);
	return (1);
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
	printf("\n");
	return (mlx_loop(core->mlx_inst_ptr));
}
