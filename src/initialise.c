/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:53:03 by lmells            #+#    #+#             */
/*   Updated: 2023/11/09 15:00:44 by lmells           ###   ########.fr       */
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

static inline void	cast_new_ray(t_raycast *caster, int x, int view_width,
						t_entity entity)
{
	caster->camera_x = 2.0f * x / (double)view_width - 1.0f;
	// printf("Camera X = %f | ", caster->camera_x);
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

		// printf("Line Height = %i | Draw Line: start y = %i, end y = %i\n", line_height, draw_start, draw_end);
		mlxge_draw_vertical_line(view, x, (t_v2i){draw_start, draw_end}, colour);
	}
	// mlxge_output_ppm(view);
	// mlxge_destroy();
}

static int	game_loop(t_layer *game_layer, double timestep)
{
	t_cub3d		*app;
	t_img_quad	*view;

	// printf("IN GAME LOOP\n");
	(void)game_layer;
	(void)timestep;
	app = cub3d();
	view = app->game_view->images_to_render->next;
	mlxge_fill(view, view->bg_colour);
	raycast(&app->raycaster, view, &app->world);
	// world = &cub3d()->world;
	// view = cub3d()->game_view;
	// if (world->player.has_moved)
	// 	update_player(world, &world->player);
	return (1);
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

static inline bool	define_viewports(t_cub3d *app, t_layer *game_layer,
						t_dimensions view_size)
{
	t_img_quad	*background;
	t_v2d		view_origin;

	view_origin = (t_v2d){0, 0};
	app->game_view = mlxge_new_viewport(&game_layer->viewport_list, view_origin,
			view_size);
	if (!app->game_view)
		return (false);
	background = mlxge_new_image(&app->game_view->images_to_render,
		view_origin, view_size);
	if (!background)
		return (false);
	draw_background(background, app->rgb);
	return (mlxge_new_image(&app->game_view->images_to_render,
		(t_v2d){0, 0}, view_size));
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
}

void	initialise(t_cub3d *app, const char *map_filepath)
{
	t_layer			*game_layer;
	t_properties	view;

	ft_bzero(app, sizeof(t_cub3d));
	if (!parse_map_file(app, map_filepath))
		exit(destroy_cub3d(app));

	view = *set_display(WIN_H, 4.0f / 3);
	*(&window()->size.width) = view.size.width;// * 2 + 2;
	mlxge_init(app, destroy_cub3d);
	if (mlxge_create_window(window()->size.width, window()->size.height, TITLE) < 0)
		mlxge_destroy();
	game_layer = mlxge_new_layer(window()->origin, window()->size, game_loop);
	if (!game_layer || !mlxge_push_layer(game_layer)
		|| !define_viewports(app, game_layer, view.size))
		mlxge_destroy();
	
	initalise_world(app);
	printf("Player Start - Position: (%.3f, %.3f) | Direction: (%.3f, %.3f)\n", app->world.player.position.x, app->world.player.position.y, app->world.player.direction.x, app->world.player.direction.y);
}
