/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 08:12:31 by lmells            #+#    #+#             */
/*   Updated: 2023/12/14 16:01:21 by lmells           ###   ########.fr       */
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

	*view_prop = display_properties(VIEW_H, WIDE_16_9);
	// printf("Game: %ix%i\n", view_prop->size.width, view_prop->size.height);
	view = mlxge_new_viewport(&game_layer->viewport_list, view_prop->origin, view_prop->size);
	if (!view)
	{
		cub3d_error("Failed to initialise game viewport because: "
			"Couldn't allocate memory");
		return ((void *)0);
	}
	view->frame->bg_colour = 0xFF0000;
	return (view);
}

bool	initialise_game_struct(t_game *game, t_window *win)
{
	struct s_display_properties	view;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (!cub3d_error("Failed to initialise game struct because: "
			"Couldn't allocate memory"));
	game->layer = mlxge_new_layer(win->origin, win->size, update);
	if (!game->layer || !mlxge_push_layer(game->layer))
		return (!cub3d_error("Failed to initialise game layer because: "
			"Couldn't allocate memory"));

	game->view = define_game_viewport(game->layer, &view);
	if (!game->view)
		return (false);
	game->hud = create_hud(game, win, &view);
	if (!game->hud)
		return (false);
	mlxge_push_image_z_buffer(game->layer, game->view->frame, 0);
	mlxge_push_image_z_buffer(game->layer, game->hud->background_image, 0);
	mlxge_push_image_z_buffer(game->layer, game->hud->minimap->frame, 1);
	return (true);
}

// Set window properties - dimensions, aspect ratio & origin.
// Initialise MLXGE instance - bind cub3d struct and destroy function.
// Create a new window with defined window properties & title.
static inline void	initialise_mlxge_application(t_cub3d *app)
{
	t_window	*win;

	win = set_window_size(WIN_H, SQUARE_5_4);
	// printf("Window: %ix%i\n", win->size.width, win->size.height);
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
