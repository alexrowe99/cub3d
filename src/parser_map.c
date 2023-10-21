/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:19:55 by lmells            #+#    #+#             */
/*   Updated: 2023/10/16 09:41:56 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
	check.visited = ft_calloc(app->map_dim.height * app->map_dim.width + 1, sizeof(bool));
	if (check.visited)
	{
		valid = validate_map_floodfill(&check, v2d_to_v2i(app->player.pos),
				'1');
		if (!valid)
			cub3d_error("Invalid parse: Map is not enclosed by wall tiles");
		free(check.visited);
	}
	ft_free_str_2d(check.grid, check.dim.height);
	return (valid);
}

static char	**populate_map_tiles(char **data, t_dimensions dim)
{
	int		i;
	char	**tiles;

	tiles = malloc((dim.height + 1) * sizeof(char *));
	if (!tiles)
	{
		cub3d_error("Something unexpected happened");
		return (NULL);
	}
	tiles[dim.height] = NULL;
	i = -1;
	while (++i < dim.height)
	{
		tiles[i] = malloc(dim.width + 1);
		if (!tiles[i])
		{
			cub3d_error("Something unexpected happened");
			ft_free_str_2d(tiles, i);
			return (NULL);
		}
		tiles[i][dim.width] = '\0';
		ft_memset(tiles[i], ' ', dim.width);
		ft_memcpy(tiles[i], data[i], ft_strlen(data[i]));
	}
	return (tiles);
}

static bool	validate_store_player_spawn(t_cub3d *app, t_dimensions map_dim)
{
	bool	has_spawn;
	bool	spawn_found;

	has_spawn = false;
	while (--map_dim.height)
	{
		map_dim.width = -1;
		while (++map_dim.width < app->map_dim.width)
		{
			spawn_found = is_spawn_tile(app->map_tiles[map_dim.height][map_dim.width],
					&app->player);
			if (spawn_found && has_spawn)
				return (!cub3d_error("Invalid parse: Multiple spawn points "\
						"detected in map file"));
			else if (spawn_found && !has_spawn)
			{
				app->player.pos = v2d(map_dim.width, map_dim.height);
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

	app->map_dim.height = m_file->line_count - m_file->it;
	if (!app->map_dim.height)
		return (!cub3d_error("Invalid parse: There are no map tiles present"));
	while (m_file->it != m_file->line_count)
	{
		if (!validate_map_tiles(m_file->contents[m_file->it]))
			return (false);
		m_width = ft_strlen(m_file->contents[m_file->it]);
		if (app->map_dim.width < m_width)
			app->map_dim.width = m_width;
		m_file->it++;
	}
	offset = m_file->it - app->map_dim.height;
	app->map_tiles = populate_map_tiles(&m_file->contents[offset], app->map_dim);
	valid = app->map_tiles && validate_store_player_spawn(app, app->map_dim);
	return (valid && check_map_enclosed(app));
}
