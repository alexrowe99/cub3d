/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:53:03 by lmells            #+#    #+#             */
/*   Updated: 2023/10/27 21:46:27 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	game_loop(t_layer *game_layer)
{
	(void)game_layer;
	return (1);
}

typedef struct s_display_properties
{
	t_v2i			origin;
	t_dimensions	size;
	double			aspect_ratio;
}	t_properties;

enum e_viewport_count
{
	DEBUG,
	GAME,
	COUNT_VIEWS
};

static inline bool	define_viewports(t_layer *game_layer,
						t_dimensions view_size)
{
	t_v2i		view_origin;
	t_viewport	*views[COUNT_VIEWS];

	view_origin = (t_v2i){0, 0};
	views[DEBUG] = mlxge_new_viewport(&game_layer->viewport_list,
			view_origin, view_size);
	if (!views[DEBUG])
		return (false);
	view_origin.x = view_size.width + 1;
	views[GAME] = mlxge_new_viewport(&game_layer->viewport_list,
			view_origin, view_size);
	if (!views[GAME])
		return (false);
	views[DEBUG]->frame->bg_colour = 0x42F560;
	views[GAME]->frame->bg_colour = 0x534CA1;
	return (true);
}

void	initialise(t_cub3d *app, const char *map_filepath)
{
	t_layer			*game_layer;
	t_dimensions	win;
	t_properties	view;

	ft_bzero(app, sizeof(t_cub3d));
	if (!parse_map_file(app, map_filepath))
		exit(destroy_cub3d(app));
	view.aspect_ratio = 4.0f / 3;
	view.origin.x = 0;
	view.origin.y = 0;
	view.size.width = WIN_H * view.aspect_ratio;
	view.size.height = WIN_H;
	win.width = view.size.width * 2 + 1;
	win.height = view.size.height;
	mlxge_init(app, destroy_cub3d);
	if (mlxge_create_window(win.width, win.height, TITLE) < 0)
		mlxge_destroy();
	game_layer = mlxge_new_layer(view.origin, win, game_loop);
	if (!game_layer || !mlxge_push_layer(game_layer)
		|| !define_viewports(game_layer, view.size))
		mlxge_destroy();
}
