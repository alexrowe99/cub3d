/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:03:54 by lmells            #+#    #+#             */
/*   Updated: 2023/10/30 16:36:26 by lmells           ###   ########.fr       */
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

// ----- API -------------------------------------------------------------------

void	mlxge_init(void *app_struct_ptr,
			int (*destroy_app_struct_funct)(void *))
{
	*get_core()->sandbox = (struct s_user_app){.user_app_ref = app_struct_ptr,
	.user_app_destroy = destroy_app_struct_funct};
	mlxge_keyboard();
}

#define SUCCESS 0

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
