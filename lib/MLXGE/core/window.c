/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:55:47 by lmells            #+#    #+#             */
/*   Updated: 2023/10/10 14:31:48 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <events.h>

static struct s_mlxge_window	mlxge_window(void *mlx_ptr, int w, int h, char *title)
{
	struct s_mlxge_window	window;

	window =  (struct s_mlxge_window){
		.dim = dimensions(w, h),
		.id_ptr = mlx_new_window(mlx_ptr, w, h, title),
		.img = mlx_new_image(mlx_ptr, w, h)
	};
	if (!window.id_ptr || !window.img)
		mlxge_log(ERROR, ERR_WIN_FAIL" : "MLX_MEM_FAIL);
	return (window);
}

static struct s_mlxge_window	*mlxge_new_window(void *mlx_ptr, int w, int h,
									char *title)
{
	struct s_mlxge_window	*win;

	win = malloc(1 * sizeof(struct s_mlxge_window));
	if (!win)
	{
		mlxge_log(FATAL, ERR_WIN_FAIL" : Couldn't allocate memory");
		return ((void *)0);
	}
	*win = mlxge_window(mlx_ptr, w, h, title);
	if (!win->id_ptr || !win->img)
		return ((void *)0);
	return (win);
};

int	mlxge_create_window(int width, int height, char *title)
{
	void			*close_event;
	struct s_mlxge	*core;

	core = get_mlxge_core();
	mlxge_log(INFO, "Creating MLXGE window...");
	core->win = mlxge_new_window(core->mlx, width, height, title);
	if (!core->win)
		return (-1);
	mlxge_log(DEBUG, "MLXGE window (%p) properties {", core->win);
	mlxge_log(DEBUG, "\tTitle\t\t: %s", title);
	mlxge_log(DEBUG, "\tDimensions\t: %ix%i", width, height);
	mlxge_log(DEBUG, "}");
	mlxge_log(INFO, "Creating MLXGE window layer...");
	core->layers = mlxge_window_layer(core->win->dim.width, core->win->dim.height,
					mlxge_update, core->win->img);
	if (!core->layers)
	{
		mlxge_log(ERROR, ERR_WIN_FAIL" : Couldn't create MLXGE window layer");
		return (-1);
	}
	core->win->layer = core->layers;
	close_event = mlxge_new_key_event(PRESSED, KEY_ESCAPE, mlxge_destroy, 0);
	if (!close_event)
		return (-1);
	mlxge_push_event(close_event, ((t_layer *)core->layers)->event_list);
	return (0);
}

void	mlxge_destroy_window(void *mlx_ptr, void *win_ptr)
{
	struct s_mlxge_window	*win;
	
	win = (struct s_mlxge_window *)win_ptr;
	if (win->img)
	{
		mlxge_log(DEBUG, "MiniLibX is destroying image... %p", win->img);
		mlx_destroy_image(mlx_ptr, win->img);
	}
	if (win->id_ptr)
	{
		mlxge_log(DEBUG, "MiniLibX is destroying window... %p", win->id_ptr);
		mlx_destroy_window(mlx_ptr, win->id_ptr);
	}
	free(win);
}
