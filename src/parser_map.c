/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:19:55 by lmells            #+#    #+#             */
/*   Updated: 2023/09/08 12:55:57 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

typedef struct s_floodfill_map_validation
{
	t_v2i	dimensions;
	char	**grid;
	bool	*visited;
}	t_ffill;

static bool	validate_map_floodfill(t_ffill *check, t_v2i pos, int replace_c)
{
	bool	enclosed;

	if (pos.x < 0 || check->dimensions.x <= pos.x
		|| pos.y < 0 || check->dimensions.y <= pos.y)
		return (false);
	if (check->grid[pos.y][pos.x] == replace_c
		|| check->visited[pos.x + pos.y * check->dimensions.x])
		return (true);
	check->visited[pos.x + pos.y * check->dimensions.x] = true;
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
	check.dimensions = app->m_dim;
	check.visited = ft_calloc(app->m_dim.y * app->m_dim.x + 1, sizeof(bool));
	if (check.visited)
	{
		valid = validate_map_floodfill(&check, app->player.spawn, '1');
		if (!valid)
			cub3d_error("Invalid parse: Map is not enclosed by wall tiles");
		free(check.visited);
	}
	ft_free_str_2d(check.grid, check.dimensions.y);
	return (valid);
}

static char	**populate_map_tiles(char **data, t_v2i dimensions)
{
	int		i;
	char	**tiles;

	tiles = malloc((dimensions.y + 1) * sizeof(char *));
	if (!tiles)
	{
		cub3d_error("Something unexpected happened");
		return (NULL);
	}
	tiles[dimensions.y] = NULL;
	i = -1;
	while (++i < dimensions.y)
	{
		tiles[i] = malloc(dimensions.x + 1);
		if (!tiles[i])
		{
			cub3d_error("Something unexpected happened");
			ft_free_str_2d(tiles, i);
			return (NULL);
		}
		tiles[i][dimensions.x] = '\0';
		ft_memset(tiles[i], ' ', dimensions.x);
		ft_memcpy(tiles[i], data[i], ft_strlen(data[i]));
	}
	return (tiles);
}

static bool	validate_store_player_spawn(t_cub3d *app, t_v2i pos)
{
	bool	has_spawn;
	bool	spawn_found;

	has_spawn = false; 
	while (--pos.y)
	{
		pos.x = -1;
		while (++pos.x < app->m_dim.x)
		{
			spawn_found = is_spawn_tile(app->map_tiles[pos.y][pos.x],
					&app->player);
			if (spawn_found && has_spawn)
				return (!cub3d_error("Invalid parse: Multiple spawn points "\
						"detected in map file"));
			else if (spawn_found && !has_spawn)
			{
				app->player.spawn = pos;
				has_spawn = true;
			}
		}
	}
	if (!has_spawn)
		return (!cub3d_error("Invalid parse: No spawn point detected in map "\
				"file"));
	return (true);
}

bool	parse_map_tiles(t_file *m_file, t_cub3d *app)
{
	size_t	offset;
	int		m_width;
	bool	valid;

	app->m_dim.y = m_file->line_count - m_file->it;
	if (!app->m_dim.y)
		return (!cub3d_error("Invalid parse: There are no map tiles present"));
	while (m_file->it != m_file->line_count)
	{
		if (!validate_map_tiles(m_file->contents[m_file->it]))
			return (false);
		m_width = ft_strlen(m_file->contents[m_file->it]);
		if (app->m_dim.x < m_width)
			app->m_dim.x = m_width;
		m_file->it++;
	}
	offset = m_file->it - app->m_dim.y;
	app->map_tiles = populate_map_tiles(&m_file->contents[offset], app->m_dim);
	valid = app->map_tiles && validate_store_player_spawn(app, app->m_dim);
	return (valid && check_map_enclosed(app));
}
