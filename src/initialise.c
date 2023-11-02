/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:53:03 by lmells            #+#    #+#             */
/*   Updated: 2023/11/02 21:46:19 by lmells           ###   ########.fr       */
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

static inline t_v2d	gather_input(t_entity *player)
{
	t_v2d	move;

	move = (t_v2d){0.0f, 0.0f};
	if (mlxge_is_key_down(KEY_W))
	{
		move.y += player->move_speed;
	}
	if (mlxge_is_key_down(KEY_A))
	{
		move.x += player->move_speed;
	}
	if (mlxge_is_key_down(KEY_S))
	{
		move.y -= player->move_speed;
	}
	if (mlxge_is_key_down(KEY_D))
	{
		move.x -= player->move_speed;
	}
	if (move.x || move.y)
	{
		player->pos = (t_v2d){player->pos.x - move.x, player->pos.y - move.y};
		player->has_moved = true;
	}
	return (move);
}

void	camera_translate(t_cam_ortho2d *camera, t_v2d translate)
{
	camera->position = (t_v2d){
		camera->position.x + translate.x,
		camera->position.y + translate.y
	};
}

static int	game_loop(t_layer *game_layer)
{
	t_world		*world;
	t_entity	*player;
	t_v2d		player_move;

	(void)game_layer;
	world = &cub3d()->world;
	player = &cub3d()->player;
	player_move = gather_input(player);
	if (player->has_moved)
	{
		player->sprite->origin = (t_v2i){
			player->sprite->origin.x - player_move.x,
			player->sprite->origin.y - player_move.y,
		};
		player_move = (t_v2d){-player_move.x, -player_move.y};
		camera_translate(world->player_camera, player_move);
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
	view_origin.x = view_size.width + 4;
	views[GAME] = mlxge_new_viewport(&game_layer->viewport_list, view_origin,
			view_size);
	if (!views[GAME])
		return (false);
	views[GAME]->frame->bg_colour = 0xFFFFFF;//0x1ECDE8;
	return (true);
}

t_world	initalise_world(t_cub3d *app, double scale)
{
	t_world	world;

	world = (t_world){
		.scale = scale,
		.size = {app->map_dim.width * scale, app->map_dim.height * scale},
		.player_camera = (void *)0
	};

	app->player.pos = (t_v2d){
		app->player.pos.x * scale + scale / 2,
		app->player.pos.y * scale + scale / 2
	};
	app->player.move_speed = 3.0f;

	return (world);
}

void	initialise(t_cub3d *app, const char *map_filepath)
{
	int				*win_width;
	t_layer			*game_layer;
	t_properties	view;

	ft_bzero(app, sizeof(t_cub3d));
	if (!parse_map_file(app, map_filepath))
		exit(destroy_cub3d(app));

	view = *set_display(WIN_H, 1);
	win_width = &window()->size.width;
	*win_width = view.size.width * 2 + 4;
	mlxge_init(app, destroy_cub3d);
	if (mlxge_create_window(*win_width, view.size.height, TITLE) < 0)
		mlxge_destroy();

	app->world = initalise_world(app, 64);

	game_layer = mlxge_new_layer(window()->origin, window()->size, game_loop);
	if (!game_layer || !mlxge_push_layer(game_layer)
		|| !define_viewports(app, game_layer, view.size))
		mlxge_destroy();

	t_v2d	translate_player = {app->player.pos.x, app->player.pos.y};
	camera_translate(app->world.player_camera, translate_player);
}
