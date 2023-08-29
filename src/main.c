/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:10:53 by lmells            #+#    #+#             */
/*   Updated: 2023/08/29 16:08:35 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

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

static void	read_file_contents(const char *filepath, t_fcontent *file)
{
	char	*line;
	// char	*data;

	file->fd = open(filepath, O_RDONLY);
	if (file->fd < 0)
	{
		cub3d_error("Could not open file \"%s\"", filepath);
		exit(1);
	}
	line = get_next_line(file->fd);
	while (line)
	{
		// data = ft_strtrim(line, "\n");
		// if (!*data)
		// {
		// 	ft_vfree(2, &data, &line);
		// 	exit(1);
		// }

		file->line_count++;
		file->contents = ft_append_str_2d(file->contents, line);
		if (!file->contents)
		{
			cub3d_error("Could not read map file \"%s\"", filepath);
			exit(1);
		}
		free(line);
		line = get_next_line(file->fd);
	}
	close(file->fd);
}

int	get_texture_id(const char *texture_info)
{
	if (!ft_strncmp(texture_info, "NO", 2))
		return (0);
	if (!ft_strncmp(texture_info, "SO", 2))
		return (1);
	if (!ft_strncmp(texture_info, "EA", 2))
		return (2);
	if (!ft_strncmp(texture_info, "WE", 2))
		return (3);
	return (-1);
}

// bool	is_rgb_value(const char *data)
// {
// 	return (!(ft_strncmp(data, "F", 1) || ft_strncmp(data, "C", 1)));
// }

// bool	is_map_data(const char *data)
// {
	
// }

char	*validate_tetxure_file(char *path)
{
	char	*xpm;

	xpm = ft_strrchr(path, '.');
	if (!xpm || ft_strncmp(xpm, ".xpm", 4))
		return (NULL);
	return (ft_strdup(path));
}

bool	store_texture_paths(t_cub3d *app, char **data, size_t *index)
{
	(void)app;
	size_t	i;
	int		texture_id;

	i = 0;
	while (i < 4)
	{
		texture_id = get_texture_id(data[*index]);
		if (texture_id == -1)
			return (!cub3d_error("Invalid parse: "\
					"Line \"%s\" could not be recognised", data[*index]));
		i++;
	}
	if (i != 4)
		return (!cub3d_error("Invalid parse: Missing required textures in map file"));
	return (true);
}

void	initialise(t_cub3d *app, const char *filepath)
{
	// (void)app;
	size_t		i;
	bool		success;
	t_fcontent	map_file;

	ft_bzero(&map_file, sizeof(t_fcontent));
	read_file_contents(filepath, &map_file);

	ft_printf("------------------------------------------------------------\n");
	for (size_t i = 0; i < map_file.line_count && map_file.contents[i]; i++)
		ft_printf("%s", map_file.contents[i]);
	ft_printf("------------------------------------------------------------\n");

	i = 0;
	success = store_texture_paths(app, map_file.contents, &i);

	ft_free_str_2d(map_file.contents, map_file.line_count);
	if (!success)
		exit(1);
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
