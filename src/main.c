/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:10:53 by lmells            #+#    #+#             */
/*   Updated: 2023/08/31 19:07:41 by lmells           ###   ########.fr       */
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

	i = 4;
	while (i--)
	{
		if (app->texture_paths[i])
			free(app->texture_paths[i]);
		app->texture_paths[i] = NULL;
	}
}

uint64_t	rgb_to_uint64(uint8_t r, uint8_t g, uint8_t b)
{
	return (r << 16 | g << 8 | b);
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
	success = success && parse_textures_paths(&map_file, app, TEXTURE_COUNT);
	if (success)
	{
		ft_printf("------------------------------------------------------------\n");
		for (size_t i = 0; i < TEXTURE_COUNT; i++)
			ft_printf("%s\n", app->texture_paths[i]);
		ft_printf("------------------------------------------------------------\n");
	}
	success = success && parse_rgb(&map_file, app, RGB_COUNT);
	if (success)
	{
		ft_printf("------------------------------------------------------------\n");
		for (size_t i = 0; i < RGB_COUNT; i++)
			ft_printf("0x00%X\n", app->rgb_floor_ceiling[i]);
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
