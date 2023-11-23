/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:53:03 by lmells            #+#    #+#             */
/*   Updated: 2023/11/24 09:53:18 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// !! Add in game + update logic here !!
// Image bg colour is initalised with value 0xFF000000 - Transparent Pixel (Transparency: 255, Red: 0, Green: 0, Blue: 0)
// Currently only flushing the image that the raycast engine will draw to.
// World struct contains the player entity.
int	game_loop(t_layer *game_layer, double timestep)
{
	// t_world		*world;
	// world = &cub3d()->world;
	t_img_quad	*raycast_image;

	(void)timestep;
	raycast_image = game_layer->images_to_render->next;
	mlxge_fill(raycast_image, raycast_image->bg_colour);
	return (1);
}

typedef struct s_window_display_properties
{
	t_v2d			origin;
	t_dimensions	size;
	double			aspect_ratio;
}	t_window;

static t_window	*window(void)
{
	static t_window	window;

	return (&window);
}

static inline t_window	*set_display_properties(size_t win_height, double aspect_ratio)
{
	t_window	*win;

	win = window();
	*win = (t_window){
		.origin = {0, 0},
		.size = {win_height * aspect_ratio, win_height},
		.aspect_ratio = aspect_ratio
	};
	return (win);
}

// Background is just a static image with 2 rectangles.
// One for the ceiling and one for the floor.
void	draw_background(t_world *world, t_layer *game_layer)
{
	t_img_quad	*background;

	background = mlxge_new_image(&game_layer->images_to_render,
			game_layer->frame->origin, game_layer->frame->size);
	if (!background)
		return (mlxge_destroy());
	mlxge_fill_rect(background, (t_v2i){0, 0},
			(t_v2i){background->size.width, background->size.height / 2},
			world->map.ceiling_colour);
	mlxge_fill_rect(background,
			(t_v2i){0, background->size.height / 2},
			(t_v2i){background->size.width, background->size.height},
			world->map.floor_colour);
}

// Game Foreground is the image that the raycaster will draw to.
static inline void	initialise_world(t_cub3d *app, t_layer *game_layer)
{
	t_world		*world;
	t_img_quad	*game_foreground;

	world = &app->world;
	world->map.ceiling_colour = *app->rgb[ID_CEILING_RGB];
	world->map.floor_colour = *app->rgb[ID_FLOOR_RGB];
	draw_background(world, game_layer);
	game_foreground = mlxge_new_image(&game_layer->images_to_render,
			game_layer->frame->origin, game_layer->frame->size);
	if (!game_foreground)
		mlxge_destroy();
}

void	initialise(t_cub3d *app, const char *map_filepath)
{
	t_layer		*game_layer;
	t_window	*window;

	window = set_display_properties(WIN_H, 16.0f / 9);
	mlxge_init(app, destroy_cub3d);
	if (!parse_map_file(app, map_filepath)
		|| mlxge_create_window(window->size.width, window->size.height, TITLE) < 0)
		return (mlxge_destroy());
	
	// A layer is added to the render queue.
	// Shouldn't need to create any events as their is input polling with mlxge_is_key_down().
	game_layer = mlxge_new_layer(window->origin, window->size, game_loop);
	if (!game_layer || !mlxge_push_layer(game_layer))
		return (mlxge_destroy());
	initialise_world(app, game_layer);
}
