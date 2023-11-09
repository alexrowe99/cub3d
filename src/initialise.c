/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:53:03 by lmells            #+#    #+#             */
/*   Updated: 2023/11/07 19:07:04 by lmells           ###   ########.fr       */
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

static inline void	gather_input(t_entity *player, double timestep)
{
	player->move = (t_v2d){0.0f, 0.0f};
	if (mlxge_is_key_down(KEY_W))
	{
		player->move.y += player->move_speed * timestep;
	}
	if (mlxge_is_key_down(KEY_A))
	{
		player->move.x += player->move_speed * timestep;
	}
	if (mlxge_is_key_down(KEY_S))
	{
		player->move.y -= player->move_speed * timestep;
	}
	if (mlxge_is_key_down(KEY_D))
	{
		player->move.x -= player->move_speed * timestep;
	}
	if (player->move.x || player->move.y)
	{
		player->position.x -= player->move.x;
		player->position.y -= player->move.y;
		player->has_moved = true;
	}
}

void	camera_translate(t_cam_ortho2d *camera, t_v2d translate)
{
	camera->position = (t_v2d){
		camera->position.x + translate.x,
		camera->position.y + translate.y
	};
}

void	update_player(t_world *world, t_entity *player)
{
	player->has_moved = false;
	(void)world;
	// player->move = (t_v2d){-player->move.x, -player->move.y};
	// world->player.sprite->origin.x += player->move.x;
	// world->player.sprite->origin.y += player->move.y;
	// camera_translate(world->debug_camera_player, player->move);
}

struct s_dda
{
	t_v2i	map;
	t_v2d	side_distance;
	t_v2d	delta_distance;
	double	perpendicular_wall_distance;
	t_v2i	step;
	int		hit;
	int		side;
};

struct s_dda	cast_new_ray(t_world *world, t_raycast *ray)
{
	struct s_dda	dda;

	dda = (struct s_dda){0};
	dda.map = (t_v2i){(int)world->player.position.x / world->scale,
			(int)world->player.position.y / world->scale};
	// printf("\t- DDA - Map Index: [%i][%i] | ", dda.map.y, dda.map.x);
	dda.delta_distance.x = fabs(1.0f / ray->direction.x);
	dda.delta_distance.y = fabs(1.0f / ray->direction.y);
	// printf("Delta Distance: (%f, %f) | ", dda.delta_distance.x, dda.delta_distance.y);
	if (ray->direction.x < 0)
	{
		dda.step.x = -1;
		dda.side_distance.x = (world->player.position.x / world->scale - dda.map.x) * dda.delta_distance.x;
	}
	else
	{
		dda.step.x = 1;
		dda.side_distance.x = (dda.map.x + 1.0 - world->player.position.x / world->scale) * dda.delta_distance.x;
	}
	if (ray->direction.y < 0)
	{
		dda.step.y = -1;
		dda.side_distance.y = (world->player.position.y / world->scale - dda.map.y) * dda.delta_distance.y;
	}
	else
	{
		dda.step.y = 1;
		dda.side_distance.y = (dda.map.y + 1.0 - world->player.position.y / world->scale) * dda.delta_distance.y;
	}
	// printf("Step: (%i, %i) | ", dda.step.x, dda.step.y);
	// printf("Side Distance: (%f, %f)\n", dda.side_distance.x, dda.side_distance.y);
	return (dda);
}

void	raycast(t_world *world, t_raycast *raycast, t_img_quad *view)
{
	int				x;
	int				ray_count;
	struct s_dda	ray;
	// (void)world;

	mlxge_fill(view, view->bg_colour);
	ray_count = view->size.width;
	x = -1;
	while (++x < ray_count)
	{
		raycast->camera_x = 2 * x / (double)view->size.width - 1;
		// printf("%i/%i\t- Camera x cooridinate: %f | ", x + 1, ray_count, raycast->camera_x);
		// printf("Player Direction (%f, %f) | ", world->player.direction.x, world->player.direction.y);
		raycast->direction = (t_v2d){
			world->player.direction.x + raycast->plane.x * raycast->camera_x,
			world->player.direction.y + raycast->plane.y * raycast->camera_x,
		};
		// printf("Ray Direction : (%f, %f)\n", raycast->direction.x, raycast->direction.y);
		ray = cast_new_ray(world, raycast);
		while (!ray.hit)
		{
			if (ray.side_distance.x < ray.side_distance.y)
			{
				ray.side_distance.x += ray.delta_distance.x;
				ray.map.x += ray.step.x;
				ray.side = 0;
			}
			else
			{
				ray.side_distance.y += ray.delta_distance.y;
				ray.map.y += ray.step.y;
				ray.side = 1;
			}
			if (world->map.tiles[ray.map.y][ray.map.x] > '0')
				ray.hit = 1;
		}
		
		if (ray.side == 0)
			ray.perpendicular_wall_distance = ray.side_distance.x - ray.delta_distance.x;
		else
			ray.perpendicular_wall_distance = ray.side_distance.y - ray.delta_distance.y;
		
		// raycast->line_height = (int)(view->size.height / ray.perpendicular_wall_distance);
		// raycast->draw_line_start.x = (int)(-raycast->line_height / 2  + view->size.height / 2);
		// if (raycast->draw_line_start.x < 0)
		// 	raycast->draw_line_start.x = 0;
		// if (raycast->draw_line_start.x > view->size.height)
		// 	raycast->draw_line_start.x = view->size.height;
		// raycast->draw_line_start.y = (int)(raycast->line_height / 2  + view->size.height / 2);
		// if (raycast->draw_line_start.y > view->size.height)
		// 	raycast->draw_line_start.y = view->size.height - 1;
		// if (raycast->draw_line_start.y < 0)
		// 	raycast->draw_line_start.y = 0;

		int colour = 0x00AC34;
		if (ray.side == 1)
			colour /= 2;

		// printf("draw line start: %i; end %i;\n", raycast->draw_line_start.y, raycast->draw_line_start.x);

		// raycast->draw_line_start = (t_v2i){200, 500};
		mlxge_draw_vertical_line(view, x, raycast->draw_line_start, colour);
	}
	// mlxge_output_ppm(view);
	// mlxge_destroy();
}

static int	game_loop(t_layer *game_layer, double timestep)
{
	(void)game_layer;
	t_world		*world;
	t_viewport	*view;

	world = &cub3d()->world;
	view = cub3d()->game_view;
	raycast(world, &world->raycaster, view->images_to_render->next);
	gather_input(&world->player, timestep);
	if (world->player.has_moved)
		update_player(world, &world->player);
	return (1);
}

static inline bool	create_background_texture(t_viewport *view, int ceiling_rgb,
						int floor_rgb)
{
	int			half_max_y;
	t_img_quad	*background;
	t_img_quad	*foreground;
	
	background = mlxge_new_image(&view->images_to_render,
			(t_v2d){0, 0}, view->frame->size);
	if (!background)
		return (false);
	foreground = mlxge_new_image(&view->images_to_render,
			(t_v2d){0, 0}, view->frame->size);
	if (!foreground)
		return (false);
	half_max_y = view->frame->size.height / 2;
	mlxge_fill_rect(background, (t_v2i){0, 0},
		(t_v2i){view->frame->size.width, half_max_y}, ceiling_rgb);
	mlxge_fill_rect(background, (t_v2i){0, half_max_y},
		(t_v2i){view->frame->size.width, view->frame->size.height}, floor_rgb);
	return (true);
}

static bool	define_game_scene(t_world *world, t_viewport *view)
{
	if (!create_background_texture(view,
			world->map.ceiling_colour, world->map.floor_colour))
		return (false);
	world->raycaster.width = view->frame->size.width;
	world->raycaster.height = view->frame->size.height;
	return (true);
}

static inline bool	define_viewports(t_cub3d *app, t_layer *game_layer,
						t_dimensions view_size)
{
	t_v2d		view_origin;
	t_viewport	*views[COUNT_VIEWS];

	view_origin = (t_v2d){0, 0};
	views[DEBUG] = mlxge_new_viewport(&game_layer->viewport_list,
			view_origin, view_size);
	if (!views[DEBUG] || !define_debug_scene(&app->world, views[DEBUG]))
		return (false);
	view_origin.x = view_size.width + 4;
	views[GAME] = mlxge_new_viewport(&game_layer->viewport_list, view_origin,
			view_size);
	if (!views[GAME] || !define_game_scene(&app->world, views[GAME]))
		return (false);
	app->game_view = views[GAME];
	return (true);
}

static inline void	initalise_world(t_world *world, double scale, int **rgb_settings)
{
	world->scale = scale;
	world->size = (t_dimensions){
		world->map.size.width * scale, 
		world->map.size.height * scale
	};
	world->map.floor_colour = *rgb_settings[ID_FLOOR_RGB];
	world->map.ceiling_colour = *rgb_settings[ID_CEILING_RGB];
	world->player.position = (t_v2d){
		world->player.position.x * scale + scale / 2,
		world->player.position.y * scale + scale / 2
	};
	world->player.move_speed = 5.0f;
	world->raycaster.plane = (t_v2d){0.0f, 0.66f};
}

void	initialise(t_cub3d *app, const char *map_filepath)
{
	t_layer			*game_layer;
	t_properties	view;

	ft_bzero(app, sizeof(t_cub3d));
	if (!parse_map_file(app, map_filepath))
		exit(destroy_cub3d(app));
	initalise_world(&app->world, 1, app->rgb);

	view = *set_display(WIN_H, 4.0f / 3);
	*(&window()->size.width) = view.size.width * 2 + 2;
	mlxge_init(app, destroy_cub3d);
	if (mlxge_create_window(window()->size.width, window()->size.height, TITLE) < 0)
		mlxge_destroy();
	game_layer = mlxge_new_layer(window()->origin, window()->size, game_loop);
	if (!game_layer || !mlxge_push_layer(game_layer)
		|| !define_viewports(app, game_layer, view.size))
		mlxge_destroy();
	camera_translate(app->world.debug_camera_player,
		(t_v2d){app->world.player.position.x, app->world.player.position.y});
}
