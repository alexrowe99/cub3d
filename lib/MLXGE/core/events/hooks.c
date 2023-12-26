/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 20:46:10 by lmells            #+#    #+#             */
/*   Updated: 2023/12/26 13:26:53 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <events.h>
#include <core.h>

#if BUILD_OS == LINUX

void	mlxge_load_mlx_event_hooks(void *mlx_win_ptr,
			t_event_layer *event_layers)
{
	mlx_hook(mlx_win_ptr, ON_KEY_PRESS_EVENT, 1L << 0,
		mlxge_handle_key_press_events, event_layers);
	mlx_hook(mlx_win_ptr, ON_KEY_RELEASE_EVENT, 1L << 1,
		mlxge_handle_key_release_events, event_layers);
	mlx_hook(mlx_win_ptr, ON_DESTROY_EVENT, 0,
		mlxge_handle_destroy_events, event_layers);
}

#else

void	mlxge_load_mlx_event_hooks(void *mlx_win_ptr,
			t_event_layer *event_layers)
{
	mlx_hook(mlx_win_ptr, ON_KEY_PRESS_EVENT, 0,
		mlxge_handle_key_press_events, event_layers);
	mlx_hook(mlx_win_ptr, ON_KEY_RELEASE_EVENT, 0,
		mlxge_handle_key_release_events, event_layers);
	mlx_hook(mlx_win_ptr, ON_DESTROY_EVENT, 0,
		mlxge_handle_destroy_events, event_layers);
}

#endif
