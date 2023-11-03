/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:19:55 by lmells            #+#    #+#             */
/*   Updated: 2023/11/03 12:10:52 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static char	**populate_map_tiles(char **raw_tile_data, t_map *map)
{
	int		i;

	map->tiles = ft_calloc(map->size.height + 1, sizeof(char *));
	if (!map->tiles)
	{
		cub3d_error("Something unexpected happened");
		return (NULL);
	}
	i = -1;
	while (++i < map->size.height)
	{
		map->tiles[i] = malloc(map->size.width + 1);
		if (!map->tiles[i])
		{
			cub3d_error("Something unexpected happened");
			ft_free_str_2d(map->tiles, i);
			return (NULL);
		}
		map->tiles[i][map->size.width] = '\0';
		ft_memset(map->tiles[i], ' ', map->size.width);
		ft_memcpy(map->tiles[i], raw_tile_data[i],
			ft_strlen(raw_tile_data[i]));
	}
	return (map->tiles);
}

static bool	validate_store_player_spawn(t_map *map, t_dimensions map_size)
{
	bool	has_spawn;
	bool	spawn_found;

	has_spawn = false;
	while (--map_size.height)
	{
		map_size.width = -1;
		while (++map_size.width < map->size.width)
		{
			spawn_found = is_spawn_tile(map->tiles[map_size.height][map_size.width],
					&app->player);
			if (spawn_found && has_spawn)
				return (!cub3d_error("Invalid parse: Multiple spawn points "\
						"detected in map file"));
			else if (spawn_found && !has_spawn)
			{
				app->player.pos = (t_v2d){m.width, m.height};
				has_spawn = true;
			}
		}
	}
	if (!has_spawn)
		return (!cub3d_error("Invalid parse: No spawn point detected in map "\
				"file"));
	return (true);
}

typedef struct s_floodfill_map_validation
{
	t_dimensions	dim;
	char			**grid;
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

static bool	check_map_enclosed(t_cub3d *app)
{
	bool	valid;
	t_ffill	check;

	check.grid = ft_strdup_2d(app->map_tiles);
	if (!check.grid)
		return (!cub3d_error("Something unexpected happened"));
	valid = false;
	check.dim = app->map_dim;
	check.visited = ft_calloc(app->map_dim.height * app->map_dim.width + 1,
			sizeof(bool));
	if (check.visited)
	{
		valid = validate_map_floodfill(&check,
				(t_v2i){app->player.pos.x, app->player.pos.y}, '1');
		if (!valid)
			cub3d_error("Invalid parse: Map is not enclosed by wall tiles");
		free(check.visited);
	}
	ft_free_str_2d(check.grid, check.dim.height);
	return (valid);
}

bool	parse_map_tiles(t_file *m_file, t_world *world)
{
	size_t	offset;
	int		m_width;
	bool	valid;

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
	return (populate_map_tiles(&m_file->contents[offset], &world->map)
		&& validate_store_player_spawn(&world->map, world->map.size)
		&& check_map_enclosed(&world->map))
}
