/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:16:02 by lmells            #+#    #+#             */
/*   Updated: 2023/10/27 21:20:24 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>

#define ERR_WIN_CREAT "Failed to create MLXGE Window because"

static inline t_window	*new_window(int width, int height, char *title,
							void *mlx_instance)
{
	t_window	*win;

	win = ft_calloc(1, sizeof(t_window));
	if (!win)
	{
		mlxge_log(ERROR, ERR_WIN_CREAT" : Couldn't allocate memory");
		return ((void *)0);
	}
	win->size = (t_dimensions){width, height};
	win->mlx_win_ptr = mlx_new_window(mlx_instance, width, height, title);
	if (!win->mlx_win_ptr)
	{
		mlxge_log(ERROR, ERR_WIN_CREAT" : Window is NULL pointer");
		free(win);
		return ((void *)0);
	}
	return (win);
}

static int	close_window(void *param)
{
	(void)param;
	mlxge_destroy();
	return (1);
}

// ----- API -------------------------------------------------------------------

int	mlxge_create_window(int width, int height, char *title)
{
	t_mlxge		*core;
	t_layer		*win_layer;
	t_event		*close_win;

	core = get_core();
	core->mlx_window = new_window(width, height, title, core->mlx_inst_ptr);
	if (!core->mlx_window)
		return (-1);
	win_layer = create_window_layer(core->mlx_window->size);
	if (!win_layer)
		return (-1);
	mlxge_push_layer(win_layer);
	close_win = mlxge_new_key_event(PRESS, KEY_ESCAPE, close_window, 0);
	if (!close_win)
	{
		free(win_layer);
		return (-1);
	}
	mlxge_push_event(close_win, win_layer->events);
	return (0);
}
