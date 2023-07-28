/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parser_map_floodfill.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:57:05 by lmells            #+#    #+#             */
/*   Updated: 2023/07/28 18:37:04 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_cell
{
	char	value;
	ssize_t	x;
	ssize_t	y;
	bool	is_spawn;
}	t_ffcell;

static bool	floodfill(t_map_tile **tiles, t_map *data, t_ffcell cell)
{
	bool	sorrounded;

	if (cell.x < 0 || cell.x >= (ssize_t)data->map_width
		|| cell.y < 0 || cell.y >= (ssize_t)data->map_height)
		return (false);
	if (tiles[cell.y][cell.x].type == cell.value
		|| tiles[cell.y][cell.x].visited)
		return (true);
	else
		tiles[cell.y][cell.x].visited = true;
	sorrounded = true;
	cell.x += 1;
	sorrounded &= floodfill(tiles, data, cell);
	cell.x -= 2;
	sorrounded &= floodfill(tiles, data, cell);
	cell.x += 1;
	cell.y += 1;
	sorrounded &= floodfill(tiles, data, cell);
	cell.y -= 2;
	sorrounded &= floodfill(tiles, data, cell);
	return (sorrounded);
}

void	floodfill_map_validation(t_map **data, t_initialiser *init)
{
	t_ffcell	cell;

	cell.x = (*data)->spawn_coords.x;
	cell.y = (*data)->spawn_coords.y;
	cell.value = MAP_TILE_WALL;
	if (!floodfill((*data)->tiles, *data, cell))
		init->error = &(add_validation_error(&init->validation,
					ERR_INIT_MAP" : "ERR_PARSE_MAP" : map is not enclosed by "\
					"walls.")->caught_error);
}
