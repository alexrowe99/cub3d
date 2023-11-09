/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 09:20:52 by lmells            #+#    #+#             */
/*   Updated: 2023/11/07 09:35:50 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_cam_ortho2d	*create_player_camera(t_cam_ortho2d **camera, int origin_x,
						int origin_y)
{
	*camera = mlxge_new_camera_2d_orthographic((t_v2i){origin_x, origin_y});
	return (*camera);
}

t_img_quad	*draw_player_texture(t_entity *player, t_viewport *debug_view)
{
	int			circle_radius;
	t_img_quad	*player_texture;

	circle_radius = 3;
	player_texture = mlxge_new_image(&debug_view->images_to_render,
			(t_v2d){-circle_radius, -circle_radius},
			(t_dimensions){circle_radius * 2 + 1, circle_radius * 2 + 1});
	if (player_texture)
	{
		mlxge_draw_circle(player_texture, (t_v2i){circle_radius, circle_radius},
				circle_radius, 0);
		player_texture->origin = (t_v2d){
			player_texture->origin.x + player->position.x,
			player_texture->origin.y + player->position.y
		};
	}
	player->sprite = player_texture;
	return (player_texture);
}

bool	define_debug_scene(t_world *world, t_viewport *debug_view)
{
	debug_view->frame->bg_colour = 0xFFFFFF;
	world->map.sprite =  draw_map_texture(world, debug_view);
	world->player.sprite = draw_player_texture(&world->player, debug_view);
	world->debug_camera_player = create_player_camera(&debug_view->camera,
			debug_view->frame->size.width / 2,
			debug_view->frame->size.height / 2);
	return (world->map.sprite && world->player.sprite && world->debug_camera_player);
}
