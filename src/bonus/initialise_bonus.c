/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 08:12:31 by lmells            #+#    #+#             */
/*   Updated: 2023/12/13 10:50:53 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bonus/cub3d_bonus.h>

int	update(t_layer *layer, double timestep)
{
	(void)layer;
	(void)timestep;
	return (1);
}

t_viewport	*define_game_viewport(t_layer *game_layer, struct s_display_properties *view_prop)
{
	t_viewport	*view;

	*view_prop = display_properties(VIEW_H, 16.0 / 9);
	view = mlxge_new_viewport(&game_layer->viewport_list, view_prop->origin, view_prop->size);
	if (!view)
	{
		cub3d_error("Failed to initialise game viewport because: "\
			"Couldn't allocate memory");
		return ((void *)0);
	}
	view->frame->bg_colour = 0xFF0000;
	return (view);
}

// void	create_hud_background(t_viewport *)
// {

// }

t_viewport	*define_minimap_viewport(t_game *game, struct s_display_properties *game_view,
				t_window *win)
{
	t_viewport					*view;
	struct s_display_properties	minimap_view;

	minimap_view = display_properties(256, game_view->aspect_ratio);
	game->hud_size = (t_dimensions){
		.width = win->size.width,
		.height = win->size.height - game_view->size.height
	};
	minimap_view.origin = (t_v2d){
		.x = find_middle_value(win->size.width, minimap_view.size.width),
		.y = win->size.height - game->hud_size.height + find_middle_value(game->hud_size.height,
			minimap_view.size.height)
	};
	view = mlxge_new_viewport(&game->layer->viewport_list, minimap_view.origin,
			minimap_view.size);
	if (!view)
	{
		cub3d_error("Failed to initialise game viewport because: "
			"Couldn't allocate memory");
		return ((void *)0);
	}
	view->frame->bg_colour = 0x00FF00;
	// create_hud_background(view, game->hud_size);
	return (view);
}

bool	initialise_game_struct(t_game *game, t_window *win)
{
	struct s_display_properties	view;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (!cub3d_error("Failed to initialise game struct because: "\
			"Couldn't allocate memory"));
	game->layer = mlxge_new_layer(win->origin, win->size, update);
	if (!game->layer || !mlxge_push_layer(game->layer))
		return (!cub3d_error("Failed to initialise game layer because: "\
			"Couldn't allocate memory"));
	game->view = define_game_viewport(game->layer, &view);
	if (!game->view)
		return (false);
	game->minimap = define_minimap_viewport(game, &view, win);
	return (game->minimap);
}

// Set window properties - dimensions, aspect ratio & origin.
// Initialise MLXGE instance - bind cub3d struct and destroy function.
// Create a new window with defined window properties & title.
static inline void	initialise_mlxge_application(t_cub3d *app)
{
	t_window					*win;

	win = set_window_size(WIN_H, 6.0 / 5);
	mlxge_init(app, destroy_cub3d);
	if (mlxge_create_window(win->size.width, win->size.height, TITLE) < 0
		|| !initialise_game_struct(app->game, win))
		return (mlxge_destroy());
}

void	initialise(t_cub3d *app, const char *map_filepath)
{
	ft_bzero(app, sizeof(t_cub3d));
	initialise_mlxge_application(app);
	if (!parse_map_file(app, map_filepath))
		return (mlxge_destroy());
}
