/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:53:03 by lmells            #+#    #+#             */
/*   Updated: 2023/10/29 12:05:27 by lmells           ###   ########.fr       */
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
	t_cub3d		*app;
	t_entity	*player;
	t_img_quad	*map;

	(void)game_layer;
	// app = cub3d();
	// player = &app->player;
	if (mlxge_is_key_down(KEY_W))
	{
		player->pos.y -= player->velocity;
	}
	// if (mlxge_is_key_down(KEY_A))
	// {
	// 	player->pos.x -= player->velocity;
	// }
	// if (mlxge_is_key_down(KEY_S))
	// {
	// 	player->pos.y += player->velocity;
	// }
	// if (mlxge_is_key_down(KEY_D))
	// {
	// 	player->pos.x += player->velocity;
	// }
	// app->textures[MAP_TEXTURE]->origin.x -= player->pos.x;
	// app->textures[MAP_TEXTURE]->origin.y -= player->pos.y;
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
	win.width = view.size.width;// * 2 + 1;
	win.height = view.size.height;
	mlxge_init(app, destroy_cub3d);
	if (mlxge_create_window(win.width, win.height, TITLE) < 0)
		mlxge_destroy();
	game_layer = mlxge_new_layer(view.origin, win, game_loop);
	if (!game_layer || !mlxge_push_layer(game_layer)
		|| !define_viewports(app, game_layer, view.size))
		mlxge_destroy();
}
