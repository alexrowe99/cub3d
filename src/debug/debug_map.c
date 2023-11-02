/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 10:40:34 by lmells            #+#    #+#             */
/*   Updated: 2023/11/02 21:04:43 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static inline void	draw_map_tile(t_img_quad *map, t_v2i tile_pos, t_cub3d *app)
{
	int			tile;
	t_v2i		tile_start;
	t_v2i		tile_end;
	uint32_t	colour;

	tile = app->map_tiles[tile_pos.y][tile_pos.x];
	if (tile == '1' || tile == '0' || is_spawn_tile(tile, &app->player))
	{
		colour = *app->rgb_floor_ceiling[ID_FLOOR_RGB];
		if (tile == '1')
			colour = 0x00EEFF;
		tile_start = (t_v2i){
			tile_pos.x * app->world.scale + 2,
			tile_pos.y * app->world.scale + 2
		};
		tile_end = (t_v2i){
			(tile_pos.x + 1) * app->world.scale - 2,
			(tile_pos.y + 1) * app->world.scale - 2
		};
		mlxge_fill_rect(map, tile_start, tile_end, colour);
	}
}

t_img_quad	*draw_map_texture(t_cub3d *app, t_viewport *debug_view)
{
	t_v2i		tile_pos;
	t_img_quad	*map;

	map = mlxge_new_image(&debug_view->images_to_render, (t_v2i){0, 0},
		(t_dimensions){app->world.size.width, app->world.size.height});
	if (map)
	{
		tile_pos.y = -1;
		while (++tile_pos.y < app->map_dim.height)
		{
			tile_pos.x = -1;
			while (++tile_pos.x < app->map_dim.width)
				draw_map_tile(map, tile_pos, app);
		}
	}
	return (map);
}
