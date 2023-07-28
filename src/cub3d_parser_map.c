/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parser_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:06:04 by lmells            #+#    #+#             */
/*   Updated: 2023/07/28 16:40:45 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_initialiser	*get_map_dimensions(char **info, size_t row_offset,
	t_map **data, t_initialiser *init)
{
	size_t	width;

	width = 0;
	while (info[row_offset])
	{
		width = ft_strlen(info[row_offset]);
		if ((*data)->map_width < width)
			(*data)->map_width = width;
		(*data)->map_height++;
		row_offset++;
	}
	if (width <= 0)
		init->error = &(add_validation_error(&init->validation,
					ERR_INIT_MAP" : "ERR_PARSE_MAP" : could not get map "\
					"dimensions.")->caught_error);
	return (init);
}

t_map_tile	**alloc_map_tiles(size_t map_width, size_t map_height)
{
	size_t		y;
	t_map_tile	**map_tiles;

	map_tiles = ft_calloc(map_height + 1, sizeof(t_map_tile *));
	if (!map_tiles)
		return (NULL);
	y = 0;
	while (y < map_height)
	{
		map_tiles[y] = ft_calloc(map_width + 1, sizeof(t_map_tile));
		if (!map_tiles[y])
		{
			while (y--)
				free(map_tiles[y]);
			free(map_tiles);
			return (NULL);
		}
		y++;
	}
	return (map_tiles);
}

#define TILE 0
#define COORDS 1
#define VALID_MAP_TILES " 01NSEW"

static t_initialiser	*validate_tile(char *tile, bool *spawn,
	t_initialiser *init)
{
	char		*valid_tile;

	valid_tile = ft_strtrim(tile, VALID_MAP_TILES);
	if (*valid_tile)
		add_validation_error(&init->validation,
			ERR_PARSE_MAP" : "INVALID_MAP_TILES);
	free(valid_tile);
	if (*tile == 'N' || *tile == 'S' || *tile == 'E' || *tile == 'W')
	{
		if (spawn[TILE] && spawn[COORDS])
		{
			init->error = &(add_validation_error(&init->validation,
						ERR_INIT_MAP" : "ERR_PARSE_MAP" : multiple spawn "\
						"locations were detected in the map tile grid."\
						)->caught_error);
			return (init);
		}
		spawn[TILE] = true;
	}
	return (init);
}

static t_initialiser	*validate_map_tiles(bool player_spawn,
	t_map **data, t_initialiser *init)
{
	t_v2st	cell;
	
	if (!player_spawn)
		add_validation_error(&init->validation,
			ERR_INIT_MAP" : "ERR_PARSE_MAP" : no spawn location was detected " \
			"in the map tile grid.");
	cell.y = 0;
	while (cell.y < (*data)->map_height)
	{
		cell.x = 0;
		while ((*data)->tiles[cell.y][cell.x].type != MAP_TILE_NONE)
			cell.x++;
		while (cell.x < (*data)->map_width)
		{
			if ((*data)->tiles[cell.y][cell.x].type == MAP_TILE_NONE)
				(*data)->tiles[cell.y][cell.x].type = MAP_TILE_EMPTY;
			cell.x++;
		}
		cell.y++;
	}
	return (init);
}

t_initialiser	*populate_map_tiles(char **info, size_t *row_offset,
	t_map **data, t_initialiser *init)
{
	t_v2sst	cell;
	bool	spawn[2];

	ft_bzero(spawn, sizeof(bool) * 2);
	cell.y = -1;
	while (++cell.y < (ssize_t)(*data)->map_height)
	{
		cell.x = -1;
		while (++cell.x < (ssize_t)(*data)->map_width
			&& info[*row_offset][cell.x])
		{
			if (*validate_tile(&info[(*row_offset)][cell.x], spawn,
				init)->error)
				return (init);
			if (spawn[TILE] && !spawn[COORDS])
			{
				(*data)->spawn_coords.x = (size_t)cell.x;
				(*data)->spawn_coords.y = (size_t)cell.y;
				spawn[COORDS] = true;
			}
			(*data)->tiles[cell.y][cell.x].type = info[*row_offset][cell.x];
		}
		(*row_offset)++;
	}
	return (validate_map_tiles(spawn[TILE], data, init));
}
