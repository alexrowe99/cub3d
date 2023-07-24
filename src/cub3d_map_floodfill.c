/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map_floodfill.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:57:05 by lmells            #+#    #+#             */
/*   Updated: 2023/07/24 14:08:52 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

enum e_map_tile_types
{
	MAP_TILE_NONE = 0,
	MAP_TILE_EMPTY = ' ',
	MAP_TILE_FLOOR = '0',
	MAP_TILE_VALIDATE_FLOOR = '#',
	MAP_TILE_WALL = '1',
};

typedef struct s_map_tile
{
	char	type;
	bool	visited;
}	t_map_tile;

static t_map_tile	**populate(t_map_tile **tiles, t_map *data)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < data->m_height)
	{
		x = 0;
		while (x < data->m_width)
		{
			tiles[y][x].type = data->tiles[y][x];
			if (tiles[y][x].type == MAP_TILE_NONE)
				tiles[y][x].type = MAP_TILE_EMPTY;
			x++;
		}
		y++;
	}
	return (tiles);
}

static t_map_tile	**populate_map_tiles(t_map *data, t_validator *validation)
{
	size_t		i;
	t_map_tile	**tiles;

	tiles = ft_calloc(data->m_height + 1, sizeof(t_map_tile *));
	if (!tiles)
	{
		validation = add_validation_error(validation,
			"Could not initialise map tiles : "__MEM_ALLOC__);
		return (NULL);
	}
	i = 0;
	while (i < data->m_height)
	{
		tiles[i] = ft_calloc(data->m_width + 1, sizeof(t_map_tile));
		if (!tiles[i++])
		{
			validation = add_validation_error(validation,
				"Could not initialise map tiles : "__MEM_ALLOC__);
			return (NULL);
		}
	}
	return (populate(tiles, data));
}

typedef struct s_floodfill_node
{
	size_t	max_x;
	size_t	max_y;
	ssize_t	curr_x;
	ssize_t	curr_y;
	bool	is_spawn;
}	t_ffn;

bool	validate_spawn_nodes(t_map_tile **tiles, t_ffn *start,
		t_validator *validation)
{
	ssize_t	x;
	ssize_t	y;

	y = -1;
	while (++y < (int)start->max_y)
	{
		x = 0;
		while (++x < (int)start->max_x)
		{
			if (tiles[y][x].type == 'N' || tiles[y][x].type == 'S'
				|| tiles[y][x].type == 'E' || tiles[y][x].type == 'W')
			{
				if (start->is_spawn)
				{
					add_validation_error(validation,
						__ERR_MAP_INIT_FAIL__" : multiple player spawn nodes.");
					return (false);
				}
				start->curr_x = x;
				start->curr_y = y;
				start->is_spawn = true;
			}
		}
	}
	return (start->is_spawn);
}

void	fill(t_map_tile **tiles, t_ffn cell, char new_tile, char replace_tile)
{
	if (cell.curr_x < 0 || (int)cell.max_x - 1 < cell.curr_x
		|| cell.curr_y < 0 || (int)cell.max_y - 1 < cell.curr_y)
	{
		if (DEBUG)
		{
			printf("\n!!ARRAY INDEX OUT OF BOUNDS!!\n");
			printf("curr_x: %zu; curr_y: %zu", cell.curr_x, cell.curr_y);
		}
		exit(1);
	}
	
	if (tiles[cell.curr_y][cell.curr_x].visited)
		return ;
	if (tiles[cell.curr_y][cell.curr_x].type != replace_tile)
	{
		tiles[cell.curr_y][cell.curr_x].visited = true;
		return ;
	}

	printf("Floodfilled Map Tiles: '%c' -> '%c'\n", replace_tile,
		new_tile);
	for (size_t y = 0; y < cell.max_y; y++) {
		for (size_t x = 0; x < cell.max_x; x++) {
			printf("%c,", tiles[y][x].type);
		}
		printf("\n");
	}
	printf("----------------------------------------\n");

	tiles[cell.curr_y][cell.curr_x].type = new_tile;
	tiles[cell.curr_y][cell.curr_x].visited = true;

	cell.curr_x += 1;
	fill(tiles, cell, new_tile, replace_tile);

	cell.curr_x -= 2;
	fill(tiles, cell, new_tile, replace_tile);

	cell.curr_x += 1;
	cell.curr_y += 1;
	fill(tiles, cell, new_tile, replace_tile);
	
	cell.curr_y -= 2;
	fill(tiles, cell, new_tile, replace_tile);
}

t_map_tile	**floodfill(t_map_tile **tiles, t_ffn *start, char replace_tile)
{
	printf("----------------------------------------\n");
	write(1, "Begin Floodfill...\t", 19);
	if (tiles[start->curr_y][start->curr_x].type != replace_tile)
	{
		return (tiles);
	}
	fill(tiles, *start, MAP_TILE_VALIDATE_FLOOR, replace_tile);
	printf("Done!\n");
	return (tiles);
}

void	validate_map_tiles(t_map **data, t_parser *parser)
{
	t_map_tile	**tiles;

	tiles = populate_map_tiles(*data, &parser->validation);
	if (!tiles)
		return ;
	
	printf("----------------------------------------\n");
	printf("Map Tiles:\n");
	for (size_t y = 0; y < (*data)->m_height; y++) {
		for (size_t x = 0; x < (*data)->m_width; x++) {
			printf("%c,", tiles[y][x].type);
		}
		printf("\n");
	}
	printf("----------------------------------------\n");
	exit(1);

	t_ffn	start_node;

	ft_bzero(&start_node, sizeof(t_ffn));
	start_node.max_x = (*data)->m_width;
	start_node.max_y = (*data)->m_height;
	start_node.is_spawn = validate_spawn_nodes(tiles, &start_node,
			&parser->validation);
	if (!start_node.is_spawn)
	{
		if (!start_node.curr_y)
			add_validation_error(&parser->validation,
				__ERR_MAP_INIT_FAIL__" : no player spawn node found.");
		return ;
	}

	printf("Starting node = {pos x: %zu; pos y: %zu; c: %c;}\n",
		start_node.curr_x, start_node.curr_y,
		tiles[start_node.curr_y][start_node.curr_x].type);

	tiles[start_node.curr_y][start_node.curr_x].type = MAP_TILE_FLOOR;
	printf("Starting node = {pos x: %zu; pos y: %zu; c: %c;}\n",
		start_node.curr_x, start_node.curr_y,
		tiles[start_node.curr_y][start_node.curr_x].type);
	
	tiles = floodfill(tiles, &start_node, MAP_TILE_FLOOR);


	printf("----------------------------------------\n");
	printf("Floodfilled Map Tiles: '%c' -> '%c'\n", MAP_TILE_FLOOR,
		tiles[start_node.curr_y][start_node.curr_x].type);
	for (size_t y = 0; y < (*data)->m_height; y++) {
		for (size_t x = 0; x < (*data)->m_width; x++) {
			printf("%c,", tiles[y][x].type);
		}
		printf("\n");
	}
	printf("----------------------------------------\n");

	size_t y = (*data)->m_height;
	while (y--)
	{
		if (tiles[y])
			free(tiles[y]);
	}
	if (tiles)
		free(tiles);
	printf("\n----------------------------------------\n");
}
