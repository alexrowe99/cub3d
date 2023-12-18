/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:53:03 by lmells            #+#    #+#             */
/*   Updated: 2023/12/18 15:04:57 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// !! Add in game + update logic here !!
// Image bg colour is initalised with value 0xFF000000
//   - Transparent Pixel (Transparency: 255, Red: 0, Green: 0, Blue: 0)
// Currently only flushing the image that the raycast engine will draw to.
// World struct contains the player entity.
int	game_loop(t_layer *game_layer, double timestep)
{
	// t_image	*raycast_image;

	(void)timestep;
	(void)game_layer;
	// raycast_image = *game_layer->z_buffer_tree->branches[1]->image_ref;
	// mlxge_fill(raycast_image, raycast_image->bg_colour);
	return (1);
}

// Background is just a static image with 2 rectangles.
// One for the ceiling and one for the floor.
void	draw_background(t_world *world, t_layer *game_layer)
{
	(void)world;
	/* -------------------------------------------------------------------------
	// Current method for pushing stack pointer causes segfault because
	// of attempt to derefernce the address of the pointer that has collapsed
	// via the call stack.
	// -------------------------------------------------------------------------
	// t_image	*background;

	// background = mlxge_new_image(game_layer->frame->origin,
	// 	game_layer->frame->size);
	// if (!background)
	// 	return (mlxge_destroy());
	// printf("Background Image\t: ptr = %p; address = %p\n", background, &background);
	// mlxge_push_image_z_buffer(&background, 0, game_layer);
	------------------------------------------------------------------------- */

	// background = mlxge_new_image_z(game_layer, 0, game_layer->frame->origin,
	// 	game_layer->frame->size);
	// if (!background)
	// 	return (mlxge_destroy());

	t_image	*bg = mlxge_new_image(game_layer, game_layer->frame->origin,
		game_layer->frame->size);
	if (!bg)
		mlxge_destroy();



	// mlxge_fill_rect(background, (t_v2i){0, 0},
	// 	(t_v2i){background->size.width, background->size.height / 2},
	// 	*world->map.ceiling_colour);
	// mlxge_fill_rect(background,
	// 	(t_v2i){0, background->size.height / 2},
	// 	(t_v2i){background->size.width, background->size.height},
	// 	*world->map.floor_colour);
}

// Game Foreground is the image that the raycaster will draw to.
static inline void	initialise_world(t_cub3d *app, t_layer *game_layer)
{
	t_world	*world;
	// t_image	*game_foreground;

	world = &app->world;
	world->map.ceiling_colour = &app->rgb[ID_CEILING_RGB];
	world->map.floor_colour = &app->rgb[ID_FLOOR_RGB];
	draw_background(world, game_layer);
	// mlxge_destroy();

	// game_foreground = mlxge_new_image(game_layer->frame->origin,
	// 	game_layer->frame->size);
	// if (!game_foreground)
	// 	mlxge_destroy();
	// mlxge_push_image_z_buffer(game_layer, &game_foreground, 1);
}

void	initialise(t_cub3d *app, const char *map_filepath)
{
	t_layer		*game_layer;
	t_window	*window;

	window = set_window_size(WIN_H, 16.0f / 9);
	mlxge_init(app, destroy_cub3d);
	if (!parse_map_file(app, map_filepath)
		|| mlxge_create_window(window->size.width, window->size.height,
			TITLE) < 0)
		return (mlxge_destroy());
	// A layer is added to the render queue.
	// Shouldn't need to create any events as their is input polling with
	// mlxge_is_key_down().
	game_layer = mlxge_new_layer(window->origin, window->size, game_loop);
	// mlxge_push_layer always returns 1 as it cant fail.
	//   - just some norminette cheese to save line space.
	if (!game_layer || !mlxge_push_layer(game_layer))
		return (mlxge_destroy());
	initialise_world(app, game_layer);
}
