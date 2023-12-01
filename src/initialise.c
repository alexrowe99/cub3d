/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:53:03 by lmells            #+#    #+#             */
/*   Updated: 2023/11/24 10:01:11 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

typedef struct s_window_display_properties
{
	t_v2d origin;
	t_dimensions size;
	double aspect_ratio;
} t_window;

static t_window *window(void)
{
	static t_window window;

	return (&window);
}

static inline t_window *set_display_properties(size_t win_height, double aspect_ratio)
{
	t_window *win;

	win = window();
	*win = (t_window){
		.origin = {0, 0},
		.size = {win_height * aspect_ratio, win_height},
		.aspect_ratio = aspect_ratio};
	return (win);
}

// Background is just a static image with 2 rectangles.
// One for the ceiling and one for the floor.
void draw_background(t_world *world, t_layer *game_layer)
{
	t_img_quad *background;

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

// !! Add in game + update logic here !!
// Image bg colour is initalised with value 0xFF000000 - Transparent Pixel (Transparency: 255, Red: 0, Green: 0, Blue: 0)
// Currently only flushing the image that the raycast engine will draw to.
// World struct contains the player entity.
int game_loop(t_layer *game_layer, double timestep, void *app)
{
	t_world *world;
	world = &((t_cub3d *)app)->world;
	t_img_quad *raycast_image;
	t_ray raycaster;
	int screen_pos;
	double old_direction_x;
	double old_plane_x;
	screen_pos = 0;

	(void)timestep;
	raycast_image = game_layer->images_to_render->next;
	raycaster.camera_plane.x = 0.66 * world->player.direction.y;
	raycaster.camera_plane.y = -0.66 * world->player.direction.x;

	// for (int i=0;i<world->map.size.width;i++)
	// {
	// 	for (int j=0;j<world->map.size.height;j++)
	// 		printf("%d",world->map.tiles[i][j]);
	// 	printf("\n");
	// }
	// printf("\n%d\n",world->map.tiles[3][16]);
	// exit(0);
	// while (true)
	// {
	mlxge_fill(raycast_image, raycast_image->bg_colour);
	while (screen_pos < game_layer->frame->size.width)
	{
		raycaster.camera.x = 2 * screen_pos / (double)(game_layer->frame->size.width) - 1;
		raycaster.direction.x = world->player.direction.x + raycaster.camera_plane.x * raycaster.camera.x;
		raycaster.direction.y = world->player.direction.y + raycaster.camera_plane.y * raycaster.camera.x;
		raycaster.map_pos.x = (int)world->player.position.x;
		raycaster.map_pos.y = (int)world->player.position.y;
		if (raycaster.direction.x >= 0)
		{
			if (raycaster.direction.x == 0)
				raycaster.delta_distance.x = 1e30;
			else
				raycaster.delta_distance.x = fabs(1 / raycaster.direction.x);
			raycaster.step.x = 1;
			raycaster.side_distance.x = (raycaster.map_pos.x + 1.0 - world->player.position.x) * raycaster.delta_distance.x;
		}
		else
		{
			raycaster.delta_distance.x = fabs(1 / raycaster.direction.x);
			raycaster.step.x = -1;
			raycaster.side_distance.x = (world->player.position.x - raycaster.map_pos.x) * raycaster.delta_distance.x;
		}
		if (raycaster.direction.y >= 0)
		{
			if (raycaster.direction.y == 0)
				raycaster.delta_distance.y = 1e30;
			else
				raycaster.delta_distance.y = fabs(1 / raycaster.direction.y);
			raycaster.step.y = 1;
			raycaster.side_distance.y = (raycaster.map_pos.y + 1.0 - world->player.position.y) * raycaster.delta_distance.y;
		}
		else
		{
			raycaster.delta_distance.y = fabs(1 / raycaster.direction.y);
			raycaster.step.y = -1;
			raycaster.side_distance.y = (world->player.position.y - raycaster.map_pos.y) * raycaster.delta_distance.y;
		}
		raycaster.hit = 0;
		while (raycaster.hit == 0)
		{
			if (raycaster.side_distance.x < raycaster.side_distance.y)
			{
				raycaster.side_distance.x += raycaster.delta_distance.x;
				raycaster.map_pos.x += raycaster.step.x;
				raycaster.side = 0;
			}
			else
			{
				raycaster.side_distance.y += raycaster.delta_distance.y;
				raycaster.map_pos.y += raycaster.step.y;
				raycaster.side = 1;
			}
			if (world->map.tiles[raycaster.map_pos.x][raycaster.map_pos.y] > 1)
				raycaster.hit = 1;
		}
		if (raycaster.side == 0)
			raycaster.perpendicular_wall_distance = raycaster.side_distance.x - raycaster.delta_distance.x;
		else
			raycaster.perpendicular_wall_distance = raycaster.side_distance.y - raycaster.delta_distance.y;
		raycaster.line_height = (int)(WIN_H / raycaster.perpendicular_wall_distance);
		raycaster.draw_line.x = -raycaster.line_height / 2 + WIN_H / 2;
		if (raycaster.draw_line.x < 0)
			raycaster.draw_line.x = 0;
		raycaster.draw_line.y = raycaster.line_height / 2 + WIN_H / 2;
		if (raycaster.draw_line.y >= WIN_H)
			raycaster.draw_line.y = WIN_H - 1;
		// exit(0);
		mlxge_draw_vertical_line(raycast_image, screen_pos, raycaster.draw_line, 0x00FFFFFF);
		screen_pos++;
	}
	if (mlxge_is_key_down(KEY_W))
	{
		if (world->map.tiles[(int)(world->player.position.x + world->player.direction.x * world->player.move_speed)][(int)(world->player.position.y)] != 2)
			world->player.position.x += world->player.direction.x * world->player.move_speed;
		if (world->map.tiles[(int)(world->player.position.x)][(int)(world->player.position.y + world->player.direction.y * world->player.move_speed)] != 2)
			world->player.position.y += world->player.direction.y * world->player.move_speed;
	}
	if (mlxge_is_key_down(KEY_S))
	{
		if (world->map.tiles[(int)(world->player.position.x - world->player.direction.x * world->player.move_speed)][(int)(world->player.position.y)] != 2)
			world->player.position.x -= world->player.direction.x * world->player.move_speed;
		if (world->map.tiles[(int)(world->player.position.x)][(int)(world->player.position.y - world->player.direction.y * world->player.move_speed)] != 2)
			world->player.position.y -= world->player.direction.y * world->player.move_speed;
	}
	if (mlxge_is_key_down(KEY_A))
	{
		if (world->map.tiles[(int)(world->player.position.x - raycaster.camera_plane.x * world->player.move_speed)][(int)(world->player.position.y)] != 2)
			world->player.position.x -= raycaster.camera_plane.x * world->player.move_speed;
		if (world->map.tiles[(int)(world->player.position.x)][(int)(world->player.position.y - raycaster.camera_plane.y * world->player.move_speed)] != 2)
			world->player.position.y -= raycaster.camera_plane.y * world->player.move_speed;
	}
	if (mlxge_is_key_down(KEY_D))
	{
		if (world->map.tiles[(int)(world->player.position.x + raycaster.camera_plane.x * world->player.move_speed)][(int)(world->player.position.y)] != 2)
			world->player.position.x += raycaster.camera_plane.x * world->player.move_speed;
		if (world->map.tiles[(int)(world->player.position.x)][(int)(world->player.position.y + raycaster.camera_plane.y * world->player.move_speed)] != 2)
			world->player.position.y += raycaster.camera_plane.y * world->player.move_speed;
	}
	if (mlxge_is_key_down(KEY_ARROW_RIGHT))
	{
		old_direction_x = world->player.direction.x;
		world->player.direction.x = world->player.direction.x * cos(-world->player.rotation_speed) - world->player.direction.y * sin(-world->player.rotation_speed);
		world->player.direction.y = old_direction_x * sin(-world->player.rotation_speed) + world->player.direction.y * cos(-world->player.rotation_speed);
		old_plane_x = raycaster.camera_plane.x;
		raycaster.camera_plane.x = raycaster.camera_plane.x * cos(-world->player.rotation_speed) - raycaster.camera_plane.y * sin(-world->player.rotation_speed);
		raycaster.camera_plane.y = old_plane_x * sin(-world->player.rotation_speed) + raycaster.camera_plane.y * cos(-world->player.rotation_speed);
	}
	if (mlxge_is_key_down(KEY_ARROW_LEFT))
	{
		old_direction_x = world->player.direction.x;
		world->player.direction.x = world->player.direction.x * cos(world->player.rotation_speed) - world->player.direction.y * sin(world->player.rotation_speed);
		world->player.direction.y = old_direction_x * sin(world->player.rotation_speed) + world->player.direction.y * cos(world->player.rotation_speed);
		old_plane_x = raycaster.camera_plane.x;
		raycaster.camera_plane.x = raycaster.camera_plane.x * cos(world->player.rotation_speed) - raycaster.camera_plane.y * sin(world->player.rotation_speed);
		raycaster.camera_plane.y = old_plane_x * sin(world->player.rotation_speed) + raycaster.camera_plane.y * cos(world->player.rotation_speed);
	}
	// }

	return (1);
}

// Game Foreground is the image that the raycaster will draw to.
static inline void initialise_world(t_cub3d *app, t_layer *game_layer)
{
	t_world *world;
	t_img_quad *game_foreground;

	world = &app->world;
	world->map.ceiling_colour = *app->rgb[ID_CEILING_RGB];
	world->map.floor_colour = *app->rgb[ID_FLOOR_RGB];
	draw_background(world, game_layer);
	game_foreground = mlxge_new_image(&game_layer->images_to_render,
									  game_layer->frame->origin, game_layer->frame->size);
	if (!game_foreground)
		mlxge_destroy();
}

void initialise(t_cub3d *app, const char *map_filepath)
{
	t_layer *game_layer;
	t_window *window;

	window = set_display_properties(WIN_H, 16.0f / 9);
	mlxge_init(app, destroy_cub3d);
	// printf("player position: %f, %f\nplayer direction: %f, %f\n",app->world.player.position.x, app->world.player.position.y, app->world.player.direction.x, app->world.player.direction.y);
	if (!parse_map_file(app, map_filepath) || mlxge_create_window(window->size.width, window->size.height, TITLE) < 0)
		return (mlxge_destroy());

	// A layer is added to the render queue.
	// Shouldn't need to create any events as their is input polling with mlxge_is_key_down().
	game_layer = mlxge_new_layer(window->origin, window->size, game_loop);
	if (!game_layer || !mlxge_push_layer(game_layer)) // mlxge_push_layer always returns 1 as it cant fail. - just some norminette cheese to save line space.
		return (mlxge_destroy());
	initialise_world(app, game_layer);
}
