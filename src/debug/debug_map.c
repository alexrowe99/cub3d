/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 10:40:34 by lmells            #+#    #+#             */
/*   Updated: 2023/10/30 12:34:22 by lmells           ###   ########.fr       */
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
		colour = 0xFFFFFF;
		if (tile == '1')
			colour = 0x00EEFF;
		tile_start = (t_v2i){tile_pos.x * app->tile_size + 1,
					tile_pos.y * app->tile_size + 1};
		tile_end = (t_v2i){(tile_pos.x + 1) * app->tile_size - 1,
					(tile_pos.y + 1) * app->tile_size - 1};
		mlxge_fill_rect(map, tile_start, tile_end, colour);
	}
}

static inline t_v2i	offset_player_pos(t_v2d player_pos, int tile_offset,
						t_dimensions map)
{
	return ((t_v2i){-map.width + (map.width - player_pos.x) - tile_offset,
			-map.height + (map.height - player_pos.y) - tile_offset});
}

t_img_quad	*draw_map_texture(t_cub3d *app, t_viewport *debug_view)
{
	t_v2d		player_world_pos;
	t_v2i		tile_pos;
	t_img_quad	*map;

	map = mlxge_new_image(&debug_view->images_to_render, (t_v2i){0, 0},
			(t_dimensions){app->map_dim.width * app->tile_size,
			app->map_dim.height * app->tile_size});
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
	player_world_pos = (t_v2d){app->player.pos.x * app->tile_size,
			app->player.pos.y * app->tile_size};
	map->origin = offset_player_pos(player_world_pos, app->tile_size / 2,
			map->size);
	return (map);
}
