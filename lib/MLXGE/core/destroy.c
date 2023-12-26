/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:42:12 by lmells            #+#    #+#             */
/*   Updated: 2023/12/24 12:43:17 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>

#define SUCCESS 0
#if BUILD_OS == MACOS

void	mlxge_destroy(void)
{
	t_mlxge	*core;

	free(mlxge_keyboard());
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

#else

void	mlxge_destroy(void)
{
	t_mlxge	*core;

	free(mlxge_keyboard());
	core = get_core();
	if (core->event_layers)
		mlxge_destroy_event_layers(core->event_layers);
	if (core->render_layers)
		mlxge_destroy_layers(core->render_layers);
	if (core->mlx_window && core->mlx_window->mlx_win_ptr)
	{
		mlx_destroy_window(core->mlx_inst_ptr, core->mlx_window->mlx_win_ptr);
		mlx_destroy_display(core->mlx_inst_ptr);
		free(core->mlx_inst_ptr);
	}
	free(core->mlx_window);
	if (core->sandbox && core->sandbox->user_app_ref)
		core->sandbox->user_app_destroy(core->sandbox->user_app_ref);
	free(core->sandbox);
	free(core);
	printf("\n");
	mlxge_log(INFO, "MLXGE has successfully been destroyed... Exiting!");
	exit(SUCCESS);
}

#endif
