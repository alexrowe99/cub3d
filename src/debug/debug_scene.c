/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 09:20:52 by lmells            #+#    #+#             */
/*   Updated: 2023/10/29 11:54:20 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static inline bool	create_player_camera(t_cam_ortho2d **camera, int offset_x,
						int offset_y)
{
	*camera = mlxge_new_camera_2d_orthographic((t_v2i){offset_x, offset_y});
	return (*camera);
}

static inline t_img_quad	*draw_player_texture(t_viewport *debug_view)
{
	int			circle_radius;
	t_img_quad	*player;

	circle_radius = 4;
	player = mlxge_new_image(&debug_view->images_to_render,
			(t_v2i){-circle_radius + 1, -circle_radius + 1},
			(t_dimensions){circle_radius * 2, circle_radius * 2});
	if (player)
		mlxge_draw_circle(player, (t_v2i){circle_radius, circle_radius},
				circle_radius, 0xFF0000);
	return (player);
}

bool	define_debug_scene(t_cub3d *app, t_viewport *debug_view)
{
	t_dimensions	cam_offset;

	app->tile_size = 64;
	debug_view->frame->bg_colour = 0x3C3C3C;
	cam_offset = (t_dimensions){debug_view->frame->size.width / 2,
			debug_view->frame->size.height / 2};
	app->textures[MAP_TEXTURE] = draw_map_texture(app, debug_view);
	app->textures[PLAYER_TEXTURE] = draw_player_texture(debug_view);
	return (app->textures[MAP_TEXTURE] && app->textures[PLAYER_TEXTURE] 
			&& create_player_camera(&debug_view->camera, cam_offset.width,
					cam_offset.height));
}
