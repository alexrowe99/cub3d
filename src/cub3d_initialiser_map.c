/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_initialiser_map.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:36:33 by lmells            #+#    #+#             */
/*   Updated: 2023/07/26 23:25:29 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	populate_map_tiles(const char *line, t_map **data,
		t_validation *validation)
{
	static size_t	y;
	ssize_t			x;
	char			tile;

	x = -1;
	while ((size_t)++x < (*data)->map_width)
	{
		tile = 0;
		if (line[x])
			tile = line[x];
		if (tile == MAP_TILE_EMPTY || tile == MAP_TILE_FLOOR
			|| tile == MAP_TILE_WALL || tile == MAP_TILE_SPAWN_NORTH
			|| tile == MAP_TILE_SPAWN_SOUTH || tile == MAP_TILE_SPAWN_EAST
			|| tile == MAP_TILE_SPAWN_WEST)
			(*data)->tiles[y][x].type = tile;
		else
			return (add_validation_error(validation,
				ERR_INIT_MAP" : invalid map tile present.")->caught_error);
	}
	y++;
	return (false);
}
\
	// 	printf("============== GATHERING MAP TILES ===============\n");

	// size_t width = 0;
	// size_t map_row = map_file->offset[DATA_MAP];
	// while (map_row < map_file->line_count)
	// {
	// 	width = ft_strlen(map_file->data[map_row++]);
	// 	if ((*data)->map_width < width)
	// 		(*data)->map_width = width;
	// 	(*data)->map_height++;
	// }
	// if (!(*data)->map_width || !(*data)->map_height)
	// {
	// 	free_file_data(&map_file);
	// 	init->error = &(add_validation_error(&init->validation,
	// 		ERR_PARSE_MAP" : map dimensions invalid.")->caught_error);
	// 	return (init);
	// }

	// (*data)->tiles = ft_calloc((*data)->map_height + 1, sizeof(t_map_tile *));
	// if (!(*data)->tiles)
	// {
	// 	free_file_data(&map_file);
	// 	init->error = &(add_validation_error(&init->validation,
	// 		ERR_INIT_MAP" : "MEM_ALLOC)->caught_error);
	// 	return (init);
	// }
	// bool player_spawn_set = false;
	// size_t y = 0;
	// while (y < (*data)->map_height)
	// {
	// 	(*data)->tiles[y] = ft_calloc((*data)->map_width + 1,
	// 		sizeof(t_map_tile));
	// 	if (!(*data)->tiles[y])
	// 	{
	// 		free_file_data(&map_file);
	// 		init->error = &(add_validation_error(&init->validation,
	// 			ERR_INIT_MAP" : "MEM_ALLOC)->caught_error);
	// 		return (init);
	// 	}

	// 	size_t x = 0;
	// 	size_t tc = ft_strlen(map_file->data[map_file->offset[DATA_MAP] + y]);
	// 	while (x < (*data)->map_width)
	// 	{
	// 		char tile = MAP_TILE_EMPTY;
	// 		if (x < tc)
	// 			tile = map_file->data[map_file->offset[DATA_MAP] + y][x];

	// 		if (!(tile == MAP_TILE_EMPTY || tile == MAP_TILE_FLOOR
	// 			|| tile == MAP_TILE_WALL || tile == MAP_TILE_SPAWN_NORTH
	// 			|| tile == MAP_TILE_SPAWN_SOUTH || tile == MAP_TILE_SPAWN_EAST
	// 			|| tile == MAP_TILE_SPAWN_WEST))
	// 		{
	// 			free_file_data(&map_file);
	// 			init->error = &(add_validation_error(&init->validation,
	// 				ERR_PARSE_MAP" : "INVALID_MAP_TILES)->caught_error);
	// 			return (init);
	// 		}
	// 		if (tile == MAP_TILE_SPAWN_NORTH || tile == MAP_TILE_SPAWN_SOUTH
	// 			|| tile == MAP_TILE_SPAWN_EAST || tile == MAP_TILE_SPAWN_WEST)
	// 		{
	// 			if (player_spawn_set)
	// 			{
	// 				free_file_data(&map_file);
	// 				init->error = &(add_validation_error(&init->validation,
	// 					ERR_PARSE_MAP" : multiple player spawn points."\
	// 				)->caught_error);
	// 				return (init);
	// 			}
	// 			player_spawn_set = true;
	// 		}
	// 		(*data)->tiles[y][x].type = tile;
	// 		x++;
	// 	}
	// 	y++;
	// }
	// if (!player_spawn_set)
	// {
	// 	free_file_data(&map_file);
	// 	init->error = &(add_validation_error(&init->validation,
	// 		ERR_PARSE_MAP" : no player spawn point.")->caught_error);
	// 	return (init);
	// }

	// DO FLOODFILL VALIDATION HERE!!!

	// free_file_data(&map_file);
	// exit_free(data);
	// return (init);

