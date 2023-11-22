/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:53:03 by lmells            #+#    #+#             */
/*   Updated: 2023/11/22 17:35:06 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

typedef struct s_display_properties
{
	t_v2d			origin;
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

void	cast_new_ray(t_raycast *caster, int x, int view_width,
						t_entity entity)
{
	caster->camera_x = 2.0f * x / (double)view_width - 1.0f;
	caster->ray_direction = (t_v2d){
			entity.direction.x + caster->plane.x * caster->camera_x,
			entity.direction.y + caster->plane.y * caster->camera_x
	};
	caster->map_position = (t_v2i){entity.position.x, entity.position.y};
	caster->delta_distance = (t_v2d){
			fabs(1.0f / caster->ray_direction.x),
			fabs(1.0f / caster->ray_direction.y)
	};
	caster->ray_hit = false;
}

void	raycast(t_raycast *caster, t_img_quad *view, t_world *world)
{
	int	x;

	mlxge_fill(view, view->bg_colour);
	x = -1;
	while (++x < view->size.width)
	{
		cast_new_ray(caster, x, view->size.width, world->player);

		if (caster->ray_direction.x < 0)
		{
			caster->step.x = -1;
			caster->side_distance.x = (world->player.position.x - caster->map_position.x) * caster->delta_distance.x;
		}
		else
		{
			caster->step.x = 1;
			caster->side_distance.x = (caster->map_position.x + 1.0f - world->player.position.x) * caster->delta_distance.x;
		}
		if (caster->ray_direction.y < 0)
		{
			caster->step.y = -1;
			caster->side_distance.y = (world->player.position.y - caster->map_position.y) * caster->delta_distance.y;
		}
		else
		{
			caster->step.y = 1;
			caster->side_distance.y = (caster->map_position.y + 1.0f - world->player.position.y) * caster->delta_distance.y;
		}

		while (!caster->ray_hit)
		{
			if (caster->side_distance.x < caster->side_distance.y)
			{
				caster->side_distance.x += caster->delta_distance.x;
				caster->map_position.x += caster->step.x;
				caster->side = 0;
			}
			else
			{
				caster->side_distance.y += caster->delta_distance.y;
				caster->map_position.y += caster->step.y;
				caster->side = 1;
			}
			caster->ray_hit = world->map.tiles[caster->map_position.y][caster->map_position.x] > TILE_FLOOR;
		}

		if (caster->side == 0)
			caster->perpendiular_wall_distance = caster->side_distance.x - caster->delta_distance.x;
		else
			caster->perpendiular_wall_distance = caster->side_distance.y - caster->delta_distance.y;

		int	line_height = (int)(view->size.height / caster->perpendiular_wall_distance);
		int	draw_start = -line_height / 2 + view->size.height / 2;
		if (draw_start < 0)
			draw_start = 0;
		int	draw_end = line_height / 2 + view->size.height / 2;
		if (draw_end >= view->size.height)
			draw_end = view->size.height - 1;

		int	colour = 0x3CAA00;
		if (caster->side)
			colour /= 2;
		mlxge_draw_vertical_line(view, x, (t_v2i){draw_start, draw_end}, colour);
	}
}

t_v2d	player_move_forward(t_entity *player)
{
	player->move.x += player->direction.x * player->move_speed;
	player->move.y += player->direction.y * player->move_speed;
	return (player->move);
}

t_v2d	player_move_back(t_entity *player)
{
	player->move.x -= player->direction.x * player->move_speed;
	player->move.y -= player->direction.y * player->move_speed;
	return (player->move);
}

t_v2d	player_strafe_left(t_entity *player)
{
	player->move.x += player->direction.y * player->move_speed;
	player->move.y += -player->direction.x * player->move_speed;
	return (player->move);
}

t_v2d	player_strafe_right(t_entity *player)
{
	player->move.x -= player->direction.y * player->move_speed;
	player->move.y -= -player->direction.x * player->move_speed;
	return (player->move);
}

enum e_movement_direction
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	COUNT_MOVE_DIRECTION
};

struct s_movement
{
	t_v2d	(*update)(t_entity *player);
};

static struct s_movement	*movement()
{
	static bool					init;
	static struct s_movement	matricies[COUNT_MOVE_DIRECTION];

	if (!init)
	{
		matricies[FORWARD].update = player_move_forward;
		matricies[BACKWARD].update = player_move_back;
		matricies[LEFT].update = player_strafe_left;
		matricies[RIGHT].update = player_strafe_right;
		init = true;
	}
	return (matricies);
}

void	gather_input(t_world *world, double timestep)
{
	t_entity	*player;

	player = &world->player;
	player->move = (t_v2d){0};
	player->move_speed = timestep * 5.0f;
	if (mlxge_is_key_down(KEY_W))
		player->move = movement()[FORWARD].update(player);
	if (mlxge_is_key_down(KEY_S))
		player->move = movement()[BACKWARD].update(player);
	if (mlxge_is_key_down(KEY_A))
		player->move = movement()[LEFT].update(player);
	if (mlxge_is_key_down(KEY_D))
		player->move = movement()[RIGHT].update(player);
}

void	update_minimap(t_viewport *view, t_world world)
{
	view->camera->position.x += world.player.move.x * world.map.scale;
	view->camera->position.y += world.player.move.y * world.map.scale;
}

static inline void	update_world(t_world *world)
{
	world->player.position.x += world->player.move.x;
	world->player.position.y += world->player.move.y;
	world->player.sprite->origin.x += world->player.move.x * world->map.scale;
	world->player.sprite->origin.y += world->player.move.y * world->map.scale;
}

static int	game_loop(t_layer *game_layer, double timestep)
{
	t_cub3d		*app;
	t_img_quad	*view;

	(void)game_layer;
	app = cub3d();
	view = app->game_view->images_to_render->next;
	raycast(&app->raycaster, view, &app->world);
	gather_input(&app->world, timestep);
	update_minimap(app->debug_view, app->world);
	update_world(&app->world);
	return (1);
}

void	*create_map_sprite(t_img_quad **list, t_v2d view_origin,
						t_map *map)
{
	t_v2i			p;
	t_dimensions	image_size;
	int				colour;

	image_size = (t_dimensions){
		map->size.width * map->scale,
		map->size.height * map->scale
	};
	map->sprite = mlxge_new_image(list, view_origin, image_size);
	if (map->sprite)
	{
		p.y = -1;
		while (++p.y < map->size.height)
		{
			p.x = -1;
			while (++p.x < map->size.width)
			{
				if (map->tiles[p.y][p.x] == TILE_EMPTY)
					continue ;
				colour = map->floor_colour;
				if (map->tiles[p.y][p.x] == TILE_WALL)
					colour = 0x3CAA00;
				mlxge_fill_rect(map->sprite,
					(t_v2i){p.x * map->scale + 1, p.y * map->scale + 1},
					(t_v2i){(p.x + 1) * map->scale - 1, (p.y + 1) * map->scale - 1},
					colour);
			}
		}
	}
	return (map->sprite);
}

static inline void	*create_player_sprite(t_img_quad **list, t_entity *player)
{
	int	circle_radius;

	circle_radius = 4;
	player->sprite = mlxge_new_image(list, (t_v2d){-circle_radius, -circle_radius},
		(t_dimensions){circle_radius * 2 + 1, circle_radius * 2 + 1});
	if (player->sprite)
		mlxge_draw_circle(player->sprite, (t_v2i){circle_radius, circle_radius},
			circle_radius, 0xFF0000);
	return (player->sprite);
}

static inline t_viewport	*create_debug_viewport(t_viewport **list,
								t_v2d view_origin, t_dimensions view_size,
								t_world *world)
{
	t_viewport	*view;

	view = mlxge_new_viewport(list, view_origin, view_size);
	if (!view)
		return ((void *)0);
	if (!create_map_sprite(&view->images_to_render, (t_v2d){0}, &world->map)
		|| !create_player_sprite(&view->images_to_render, &world->player))
		return ((void *)0);
	view->camera = mlxge_new_camera_2d_orthographic((t_v2i){view_size.width / 2,
			view_size.height / 2});
	if (!view->camera)
		return ((void *)0);
	view->camera->position = (t_v2d){
		world->player.position.x * world->map.scale,
		world->player.position.y * world->map.scale,
	};
	world->player.sprite->origin.x += view->camera->position.x;
	world->player.sprite->origin.y += view->camera->position.y;
	return (view);
}

static inline void	draw_background(t_img_quad *view, int **rgb_settings)
{
	int	half_max_y;

	half_max_y = view->size.height / 2;
	mlxge_fill_rect(view, (t_v2i){0, 0},
		(t_v2i){view->size.width, half_max_y}, *rgb_settings[ID_CEILING_RGB]);
	mlxge_fill_rect(view, (t_v2i){0, half_max_y},
		(t_v2i){view->size.width, view->size.height},
		*rgb_settings[ID_FLOOR_RGB]);
}

void	*create_raycast_viewport(t_viewport **list,
						t_v2d view_origin, t_dimensions view_size, t_cub3d *app)
{
	t_img_quad	*background;

	app->game_view = mlxge_new_viewport(list, view_origin, view_size);
	if (!app->game_view)
		return ((void *)0);
	background = mlxge_new_image(&app->game_view->images_to_render, (t_v2d){0, 0}, view_size);
	if (!background)
		return ((void *)0);
	draw_background(background, app->rgb);
	mlxge_new_image(&app->game_view->images_to_render, (t_v2d){0, 0}, view_size);
	return (app->game_view);
}

static inline bool	define_viewports(t_cub3d *app, t_layer *game_layer,
						t_dimensions view_size)
{
	app->debug_view = create_debug_viewport(&game_layer->viewport_list,
		(t_v2d){0, 0}, view_size, &app->world);
	if (!app->debug_view)
		return (false);
	app->game_view = create_raycast_viewport(&game_layer->viewport_list,
		(t_v2d){view_size.width + 4, 0}, view_size, app);
	return (app->game_view);
}

static inline void	initalise_world(t_cub3d *app)
{
	t_world		*world;

	app->raycaster = (t_raycast){0};
	if (!app->world.player.direction.x && app->world.player.direction.y > 0)
		app->raycaster.plane = (t_v2d){-0.66f, 0};
	else if (!app->world.player.direction.x && app->world.player.direction.y < 0)
		app->raycaster.plane = (t_v2d){0.66f, 0};
	else if (!app->world.player.direction.y && app->world.player.direction.x < 0)
		app->raycaster.plane = (t_v2d){0, -0.66f};
	else if (!app->world.player.direction.y && app->world.player.direction.x > 0)
		app->raycaster.plane = (t_v2d){0, 0.66f};
	
	world = &app->world;
	world->map.floor_colour = *app->rgb[ID_FLOOR_RGB];
	world->map.ceiling_colour = *app->rgb[ID_CEILING_RGB];
	world->map.scale = 64;
	world->player.position.x += 0.5f;
	world->player.position.y += 0.5f;
	movement();
}

void	initialise(t_cub3d *app, const char *map_filepath)
{
	t_layer			*game_layer;
	t_properties	view;

	ft_bzero(app, sizeof(t_cub3d));
	if (!parse_map_file(app, map_filepath))
		exit(destroy_cub3d(app));

	view = *set_display(WIN_H, 4.0f / 3);
	*(&window()->size.width) = view.size.width * 2 + 2;
	mlxge_init(app, destroy_cub3d);
	if (mlxge_create_window(window()->size.width, window()->size.height, TITLE) < 0)
		mlxge_destroy();

	initalise_world(app);
	game_layer = mlxge_new_layer(window()->origin, window()->size, game_loop);
	if (!game_layer || !mlxge_push_layer(game_layer)
		|| !define_viewports(app, game_layer, view.size))
		mlxge_destroy();
	
	// printf("Game Layer Frame = %p\n", game_layer->frame);
	printf("Player Start - Position: d(%.3f, %.3f) i(%i, %i) | Direction: (%.3f, %.3f)\n",
		app->world.player.position.x, app->world.player.position.y,
		(int)app->world.player.position.x, (int)app->world.player.position.y,
		app->world.player.direction.x, app->world.player.direction.y);
}
