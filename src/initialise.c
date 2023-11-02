/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:53:03 by lmells            #+#    #+#             */
/*   Updated: 2023/11/02 15:40:26 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

enum e_viewport_count
{
	DEBUG,
	GAME,
	COUNT_VIEWS
};

typedef struct s_display_properties
{
	t_v2i			origin;
	t_dimensions	size;
	double			aspect_ratio;
}	t_properties;

static t_properties	*window(void)
{
	static t_properties	window;

	return (&window);
}

static inline t_properties	*set_display(size_t win_height, double aspect_ratio)
{
	t_properties	*win;

	win = window();
	*win = (t_properties){
		.origin = {0, 0},
		.size = {win_height * aspect_ratio, win_height},
		.aspect_ratio = aspect_ratio
	};
	return (win);
}

void	camera_translate_world_pos(t_cam_ortho2d *camera, t_world *world,
			t_v2i translate)
{
	double	scale_world_x = (double)(translate.x) / world->size.width;
	double	scale_world_y = (double)(translate.y) / world->size.height;

	double	scale_display_x = (int)window()->size.width * scale_world_x;
	double	scale_display_y = (int)window()->size.height * scale_world_y;

	camera->world_pos.x -= translate.x;
	camera->world_pos.y -= translate.y;
	camera->offset.x += (int)scale_world_x;
	camera->offset.y += (int)scale_world_y;

	printf("DISPLAY: size(%f, %f)\n", (double)window()->size.width, (double)window()->size.height);
	printf("WORLD: size(%f, %f)\n", (double)world->size.width, (double)world->size.height);
	printf("CAMERA: screen_pos (%f, %f); world_pos (%f, %f); offset(%f, %f)\n",
		camera->sceen_pos.x, camera->sceen_pos.y, camera->world_pos.x, camera->world_pos.y,
		(double)camera->offset.x, (double)camera->offset.y);
	printf("WORLD TRANSLATE SCALE: (%f, %f)\n", scale_world_x, scale_world_y);
	printf("WORLD TRANSLATE: (%d, %d)\n", (int)scale_display_x, (int)scale_display_y);
	printf("\n");
}

static inline t_v2i	gather_input(t_entity *player)
{
	t_v2i	move;

	move = (t_v2i){0, 0};
	if (mlxge_is_key_down(KEY_W))
	{
		move.y -= player->velocity;
	}
	if (mlxge_is_key_down(KEY_A))
	{
		move.x -= player->velocity;
	}
	if (mlxge_is_key_down(KEY_S))
	{
		move.y += player->velocity;
	}
	if (mlxge_is_key_down(KEY_D))
	{
		move.x += player->velocity;
	}
	if (move.x || move.y)
		player->has_moved = true;
	return (move);
}

static int	game_loop(t_layer *game_layer)
{
	t_world		*world;
	t_entity	*player;
	t_v2i		player_move;

	(void)game_layer;
	world = &cub3d()->world;
	player = &cub3d()->player;
	player_move = gather_input(player);
	if (player->has_moved)
	{
		player_move.x = -player_move.x;
		player_move.y = -player_move.y;
		camera_translate_world_pos(cub3d()->world.player_camera, world,
			player_move);
		player->has_moved = false;
	}
	return (1);
}

static inline bool	define_viewports(t_cub3d *app, t_layer *game_layer,
						t_dimensions view_size)
{
	t_v2i		view_origin;
	t_viewport	*views[COUNT_VIEWS];

	view_origin = (t_v2i){0, 0};
	views[DEBUG] = mlxge_new_viewport(&game_layer->viewport_list,
			view_origin, view_size);
	if (!views[DEBUG] || !define_debug_scene(app, views[DEBUG]))
		return (false);
	// view_origin.x = view_size.width + 1;
	// views[GAME] = mlxge_new_viewport(&game_layer->viewport_list,
	// 		view_origin, view_size);
	// if (!views[GAME])
	// 	return (false);
	// views[GAME]->frame->bg_colour = 0x3C3C3C;//0x1ECDE8;
	return (true);
}

t_world	initalise_world(t_cub3d *app)
{
	app->tile_size = 32;
	app->player.velocity = 2.5f;

	return ((t_world){
		.size = {app->map_dim.width * app->tile_size, app->map_dim.height * app->tile_size},
		.scale = app->tile_size
	});
}

void	initialise(t_cub3d *app, const char *map_filepath)
{
	t_layer			*game_layer;
	t_dimensions	win;
	t_properties	*view;

	ft_bzero(app, sizeof(t_cub3d));
	if (!parse_map_file(app, map_filepath))
		exit(destroy_cub3d(app));

	view = set_display(WIN_H, 4.0f / 3);
	win.width = view->size.height * view->aspect_ratio;
	win.height = view->size.height;
	
	mlxge_init(app, destroy_cub3d);
	if (mlxge_create_window(win.width, win.height, TITLE) < 0)
		mlxge_destroy();

	app->world = initalise_world(app);

	game_layer = mlxge_new_layer(view->origin, win, game_loop);
	if (!game_layer || !mlxge_push_layer(game_layer)
		|| !define_viewports(app, game_layer, view->size))
		mlxge_destroy();

	t_v2i	translate_player = {-app->world.size.width, -app->world.size.height};
	camera_translate_world_pos(app->world.player_camera, &app->world, translate_player);
}
