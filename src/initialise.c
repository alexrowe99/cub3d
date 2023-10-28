/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:53:03 by lmells            #+#    #+#             */
/*   Updated: 2023/10/29 00:00:12 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

enum e_viewport_count
{
	DEBUG,
	GAME,
	COUNT_VIEWS
};

static int	game_loop(t_layer *game_layer)
{
	(void)game_layer;
	return (1);
}

static inline bool	create_player_camera(t_cam_ortho2d **camera, int offset_x,
						int offset_y)
{
	*camera = mlxge_new_camera_2d_orthographic((t_v2i){offset_x, offset_y});
	return (*camera);
}

static inline bool	define_debug_scene(t_viewport *debug_view)
{
	int			circle_radius;
	t_img_quad	*player;

	circle_radius = 4;
	player = mlxge_new_image(&debug_view->images_to_render,
			(t_v2i){-circle_radius + 1, -circle_radius + 1},
			(t_dimensions){circle_radius * 2, circle_radius * 2});
	if (!player
		|| !create_player_camera(&debug_view->camera,
		debug_view->frame->size.width / 2, debug_view->frame->size.height / 2))
		return (false);
	mlxge_fill(player, player->bg_colour);
	mlxge_draw_circle(player, (t_v2i){circle_radius, circle_radius},
			circle_radius, 0xFF0000);
	debug_view->frame->bg_colour = 0x3C3C3C;
	return (true);
}

static inline bool	define_viewports(t_layer *game_layer,
						t_dimensions view_size)
{
	t_v2i		view_origin;
	t_viewport	*views[COUNT_VIEWS];

	view_origin = (t_v2i){0, 0};
	views[DEBUG] = mlxge_new_viewport(&game_layer->viewport_list,
			view_origin, view_size);
	if (!views[DEBUG] || !define_debug_scene(views[DEBUG]))
		return (false);
	view_origin.x = view_size.width + 1;
	views[GAME] = mlxge_new_viewport(&game_layer->viewport_list,
			view_origin, view_size);
	if (!views[GAME])
		return (false);
	views[GAME]->frame->bg_colour = 0x3C3C3C;//0x1ECDE8;
	return (true);
}

typedef struct s_display_properties
{
	t_v2i			origin;
	t_dimensions	size;
	double			aspect_ratio;
}	t_properties;

void	initialise(t_cub3d *app, const char *map_filepath)
{
	t_layer			*game_layer;
	t_dimensions	win;
	t_properties	view;

	ft_bzero(app, sizeof(t_cub3d));
	if (!parse_map_file(app, map_filepath))
		exit(destroy_cub3d(app));
	view.aspect_ratio = 4.0f / 3;
	view.origin.x = 0;
	view.origin.y = 0;
	view.size.width = WIN_H * view.aspect_ratio;
	view.size.height = WIN_H;
	win.width = view.size.width * 2 + 1;
	win.height = view.size.height;
	mlxge_init(app, destroy_cub3d);
	if (mlxge_create_window(win.width, win.height, TITLE) < 0)
		mlxge_destroy();
	game_layer = mlxge_new_layer(view.origin, win, game_loop);
	if (!game_layer || !mlxge_push_layer(game_layer)
		|| !define_viewports(game_layer, view.size))
		mlxge_destroy();
}
