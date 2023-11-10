/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:19:55 by lmells            #+#    #+#             */
/*   Updated: 2023/11/10 09:44:10 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	**populate_map_tiles(char **raw_tile_data, t_map *map)
{
	t_v2i	it;

	map->tiles = ft_calloc(map->size.height + 1, sizeof(int *));
	if (!map->tiles)
	{
		cub3d_error("Something unexpected happened");
		return (NULL);
	}
	it.y = -1;
	while (++it.y < map->size.height)
	{
		map->tiles[it.y] = ft_calloc(map->size.width + 1, sizeof(int));
		if (!map->tiles[it.y])
		{
			cub3d_error("Something unexpected happened");
			ft_free_2d_int_n(map->tiles, map->size.height);
			return (NULL);
		}
		it.x = -1;
		while (++it.x < map->size.width && raw_tile_data[it.y][it.x])
			map->tiles[it.y][it.x] = store_tile(raw_tile_data[it.y][it.x]);
		while (it.x < map->size.width)
			map->tiles[it.y][it.x++] = TILE_EMPTY;
	}
	return (map->tiles);
}

static bool	validate_store_player_spawn(t_world *world, t_dimensions it)
{
	int		tile;
	bool	has_spawn;
	bool	spawn_found;

	has_spawn = false;
	while (--it.height)
	{
		it.width = -1;
		while (++it.width < world->map.size.width)
		{
			tile = world->map.tiles[it.height][it.width];
			spawn_found = is_spawn_tile(tile, &world->player);
			if (spawn_found && has_spawn)
				return (!cub3d_error("Invalid parse: Multiple spawn points "\
						"detected in map file"));
			else if (spawn_found && !has_spawn)
			{
				world->map.tiles[it.height][it.width] = TILE_FLOOR;
				world->player.position = (t_v2d){it.width, it.height};
				has_spawn = true;
			}
		}
	}
	return (has_spawn);
}

typedef struct s_floodfill_map_validation
{
	t_dimensions	dim;
	int				**grid;
	bool			*visited;
}	t_ffill;

static bool	validate_map_floodfill(t_ffill *check, t_v2i pos, int replace_c)
{
	bool	enclosed;

	if (pos.x < 0 || check->dim.width <= pos.x
		|| pos.y < 0 || check->dim.height <= pos.y)
		return (false);
	if (check->grid[pos.y][pos.x] == replace_c
		|| check->visited[pos.x + pos.y * check->dim.width])
		return (true);
	check->visited[pos.x + pos.y * check->dim.width] = true;
	check->grid[pos.y][pos.x] = replace_c;
	enclosed = true;
	pos.y += 1;
	enclosed &= validate_map_floodfill(check, pos, replace_c);
	pos.y -= 2;
	enclosed &= validate_map_floodfill(check, pos, replace_c);
	pos.y += 1;
	pos.x += 1;
	enclosed &= validate_map_floodfill(check, pos, replace_c);
	pos.x -= 2;
	enclosed &= validate_map_floodfill(check, pos, replace_c);
	return (enclosed);
}

static bool	check_map_enclosed(t_world *world)
{
	bool	valid;
	t_ffill	check;

	check.grid = ft_dup_2d_int_n(world->map.tiles, world->map.size.height);
	if (!check.grid)
		return (!cub3d_error("Something unexpected happened"));
	valid = false;
	check.dim = world->map.size;
	check.visited = ft_calloc(check.dim.width * check.dim.height + 1,
			sizeof(bool));
	if (check.visited)
	{
		valid = validate_map_floodfill(&check,
				(t_v2i){world->player.position.x, world->player.position.y}, TILE_WALL);
		if (!valid)
			cub3d_error("Invalid parse: Map is not enclosed by wall tiles");
		free(check.visited);
	}
	ft_free_2d_int_n(check.grid, check.dim.height);
	return (valid);
}

bool	parse_map_tiles(t_file *m_file, t_world *world)
{
	size_t	offset;
	int		m_width;

	world->map.size.height = m_file->line_count - m_file->it;
	if (!world->map.size.height)
		return (!cub3d_error("Invalid parse: There are no map tiles present"));
	while (m_file->it != m_file->line_count)
	{
		if (!validate_map_tiles(m_file->contents[m_file->it]))
			return (false);
		m_width = ft_strlen(m_file->contents[m_file->it]);
		if (world->map.size.width < m_width)
			world->map.size.width = m_width;
		m_file->it++;
	}
	offset = m_file->it - world->map.size.height;
	if (!populate_map_tiles(&m_file->contents[offset], &world->map))
		return (false);
	if (!validate_store_player_spawn(world, world->map.size))
		return (!cub3d_error("Invalid parse: No spawn point detected in map "\
				"file"));
	return (check_map_enclosed(world));
}
