/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:03:54 by lmells            #+#    #+#             */
/*   Updated: 2023/12/24 12:42:26 by lmells           ###   ########.fr       */
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
			int (*destroy_app_struct_funct)())
{
	*get_core()->sandbox = (struct s_user_app){.user_app_ref = app_struct_ptr,
	.user_app_destroy = destroy_app_struct_funct};
	mlxge_keyboard();
}
