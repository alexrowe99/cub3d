/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:10:53 by lmells            #+#    #+#             */
/*   Updated: 2023/09/05 16:25:09 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	cub3d_error(const char *format_message, ...)
{
	char	*output;
	va_list	argp;

	ft_printf("\e[0;91mError\e[0m\n");
	va_start(argp, format_message);
	ft_vasprintf(&output, format_message, argp);
	va_end(argp);
	if (errno)
		perror(output);
	else
		ft_printf("%s\n", output);
	free(output);
	return (true);
}

static bool	validate_args(int ac, char **av)
{
	char	*ext;

	if (ac != 2)
		return (!cub3d_error("Incorrect number of arguments"));
	ext = ft_strrchr(av[1], '.');
	if (!ext || ft_strncmp(".cub", ext, 4))
		return (!cub3d_error("Argument \"%s\" is not a .cub map file", av[1]));
	return (true);
}

static bool	read_file_contents(const char *filepath, t_file *file)
{
	bool	error;
	char	*line;
	char	*info;

	file->fd = open(filepath, O_RDONLY);
	if (file->fd < 0)
		return (!cub3d_error("Could not open file \"%s\"", filepath));
	error = false;
	line = get_next_line(file->fd);
	while (line && !error)
	{
		info = ft_strtrim(line, "\r\n");
		if (*info)
		{
			file->line_count++;
			file->contents = ft_append_str_2d(file->contents, info);
			if (!file->contents)
				error = cub3d_error("Could not read map file \"%s\"",
						filepath);
		}
		ft_vfree(2, &line, &info);
		line = get_next_line(file->fd);
	}
	close(file->fd);
	return (!error);
}

static void	destory_cub3d(t_cub3d *app)
{
	size_t	i;

	i = TEXTURE_COUNT;
	while (--i)
		ft_vfree(1, &app->texture_paths[i]);
	if (app->map_tiles)
	{
		while (--app->m_dim.y)
			ft_vfree(1, &app->map_tiles[app->m_dim.y]);
		free(app->map_tiles);
	}
	app->map_tiles = NULL;
}

uint64_t	rgb_to_uint64(uint8_t r, uint8_t g, uint8_t b)
{
	return (r << 16 | g << 8 | b);
}

bool	is_spawn_tile(int c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	valid_character(int c)
{
	return (c == ' ' || c == '0' || c == '1' || is_spawn_tile(c));
}

bool	validate_map_tiles(const char *line)
{
	while (*line != '\0')
	{
		if (!valid_character(*line))
			return (!cub3d_error("Invalid parse: Line \"%s\" contains invalid "\
					"character '%i'", line, *line));
		line++;
	}
	return (true);
}

char	**populate_map_tiles(char **data, t_v2i dimensions)
{
	size_t	i;
	char	**tiles;

	tiles = malloc((dimensions.y + 1) * sizeof(char *));
	if (!tiles)
	{
		cub3d_error("Something unexpected happened");
		return (NULL);
	}
	tiles[dimensions.y] = NULL;
	i = 0;
	while (i < (size_t)dimensions.y)
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
		i++;
	}
	return (tiles);
}

bool	get_player_spawn(t_cub3d *app)
{
	t_v2i	pos;
	bool	has_spawn;
	bool	spawn_found;

	has_spawn = false;
	pos.y = 0;
	while (pos.y < app->m_dim.y)
	{
		pos.x = 0;
		while (pos.x < app->m_dim.x)
		{
			spawn_found = is_spawn_tile(app->map_tiles[pos.y][pos.x]);
			if (spawn_found && has_spawn)
				return (!cub3d_error("Invalid parse: Multiple spawn points "\
						"detected in map file"));
			else if (spawn_found && !has_spawn)
			{
				app->player_spawn = pos;
				has_spawn = true;
			}
			pos.x++;
		}
		pos.y++;
	}
	if (!has_spawn)
		return (!cub3d_error("Invalid parse: No spawn point detected in map "\
				"file"));
	return (true);
}

// bool	validate_map_floodfill(t_cub3d *app, t_v2i pos, int check_c, int replace_c)
// {
// 	bool	enclosed;

// 	if (pos.x < 0 || app->m_dim.x < pos.x || pos.y < 0 || app->m_dim.y < pos.y)
// 		return (-1);
// 	if (app->map_tiles[pos.y][pos.x] == check_c)
// 		return (0);
// 	app->map_tiles[pos.y][pos.x] = replace_c;
// 	enclosed = true;
// 	pos.x += 1;
// 	enclosed &= floodfill(app, pos, check_c, replace_c);
// }

bool	parse_map_tiles(t_file *m_file, t_cub3d *app)
{
	size_t	offset;
	size_t	m_width;
	bool	valid;

	app->m_dim.y = m_file->line_count - m_file->it;
	if (!app->m_dim.y)
		return (!cub3d_error("Invalid parse: There are no map tiles present"));
	while (m_file->it != m_file->line_count)
	{
		if (!validate_map_tiles(m_file->contents[m_file->it]))
			return (false);
		m_width = ft_strlen(m_file->contents[m_file->it]);
		if ((size_t)app->m_dim.x < m_width)
			app->m_dim.x = m_width;
		m_file->it++;
	}
	offset = m_file->it - app->m_dim.y;
	app->map = populate_map_tiles(&m_file->contents[offset], app->m_dim);
	valid = app->map && get_player_spawn(app);
	// if (valid && !validate_map_floodfill())
	// 	cub3d_error("Invalid parse: Map is not enclosed by wall tiles");
	return (valid);
}

void	initialise(t_cub3d *app, const char *filepath)
{
	bool	success;
	t_file	map_file;

	ft_bzero(&map_file, sizeof(t_file));
	success = read_file_contents(filepath, &map_file);
	if (success)
	{
		ft_printf("------------------------------------------------------------\n");
		for (size_t i = 0; i < map_file.line_count && map_file.contents[i]; i++)
			ft_printf("%s\n", map_file.contents[i]);
		ft_printf("------------------------------------------------------------\n");
	}
	success &= parse_textures_paths(&map_file, app, TEXTURE_COUNT);
	if (success)
	{
		ft_printf("------------------------------------------------------------\n");
		for (size_t i = 0; i < TEXTURE_COUNT; i++)
			ft_printf("%s\n", app->texture_paths[i]);
		ft_printf("------------------------------------------------------------\n");
	}
	success &= parse_rgb(&map_file, app, RGB_COUNT);
	if (success)
	{
		ft_printf("------------------------------------------------------------\n");
		for (size_t i = 0; i < RGB_COUNT; i++)
			ft_printf("0x00%X\n", app->rgb_floor_ceiling[i]);
		ft_printf("------------------------------------------------------------\n");
	}
	success &= parse_map_tiles(&map_file, app);
	if (success)
	{
		ft_printf("------------------------------------------------------------\n");
		for (size_t y = 0; y < (size_t)app->m_dim.y; y++)
		{
			for (size_t x = 0; x < (size_t)app->m_dim.x; x++)
				ft_printf("%c, ", app->map[y][x].tile);
			ft_printf("\n");
		}
		ft_printf("------------------------------------------------------------\n");
	}

	ft_free_str_2d(map_file.contents, map_file.line_count);
	destory_cub3d(app);
	if (!success)
		exit(1);
	ft_printf("Map is valid!\n");
}

int	main(int ac, char **av)
{
	t_cub3d	app;

	if (!validate_args(ac, av))
		return (1);
	ft_bzero(&app, sizeof(t_cub3d));
	initialise(&app, av[1]);
	return (0);
}
