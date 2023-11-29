/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 08:12:31 by lmells            #+#    #+#             */
/*   Updated: 2023/11/29 16:36:27 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bonus/cub3d_bonus.h>

int	update(t_layer *layer, double timestep)
{
	(void)layer;
	(void)timestep;
	return (1);
}

static inline void	initialise_mlxge_application(t_cub3d *app,
						struct s_display_properties *view_ptr)
{
	t_window	*win;

	// Set window properties - dimensions, aspect ratio & origin.
	win = set_window_size(WIN_H, 4.0f / 3);
	
	// Initialise MLXGE instance.
	mlxge_init(app, destroy_cub3d);

	// Create a new window with defined window properties & title.
	if (mlxge_create_window(win->size.width, win->size.height, TITLE) < 0)
		return (mlxge_destroy());

	// Initialising the 'Game' screen - (What is visible to the user)
	app->game = ft_calloc(1, sizeof(t_game));
	if (!app->game)
		return (mlxge_destroy());

	// Create the game layer & push onto layer stack.	
	app->game->layer = mlxge_new_layer(win->origin, win->size, update);
	if (!app->game->layer || !mlxge_push_layer(app->game->layer))
		return (mlxge_destroy());

	// Define 16:9 viewport for game.
	*view_ptr = display_properties(450, 16.0f / 9);
	// Create the game viewport.
	//   - This will render the raycasting game (What the player see's 2.5D).
	app->game->view = mlxge_new_viewport(&app->game->layer->viewport_list,
			view_ptr->origin, view_ptr->size);
	if (!app->game->view)
		return (mlxge_destroy());
}

void	initialise(t_cub3d *app, const char *map_filepath)
{
	struct s_display_properties	view;

	ft_bzero(app, sizeof(t_cub3d));
	initialise_mlxge_application(app, &view);
	if (!parse_map_file(app, map_filepath))
		return (mlxge_destroy());

	t_viewport	*g_view = app->game->view;
	t_img_quad	*img = mlxge_new_image(&g_view->images_to_render,
			view.origin, view.size);
	if (!img)
		return (mlxge_destroy());
	mlxge_fill(img, 0xFFFFFF);
	mlxge_output_ppm(img);
	free(app->game);
}
