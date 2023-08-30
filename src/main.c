/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:10:53 by lmells            #+#    #+#             */
/*   Updated: 2023/08/29 23:25:47 by lmells           ###   ########.fr       */
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

static bool	read_file_contents(const char *filepath, t_fcontent *file)
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

int	get_texture_path_id(const char *texture_info)
{
	int	texture_id;

	texture_id = -2;
	if (!ft_strncmp(texture_info, "NO", 2))
		texture_id = 0;
	else if (!ft_strncmp(texture_info, "SO", 2))
		texture_id = 1;
	else if (!ft_strncmp(texture_info, "EA", 2))
		texture_id = 2;
	else if (!ft_strncmp(texture_info, "WE", 2))
		texture_id = 3;
	else
		texture_id = -1;
	return (texture_id);
}

bool	store_texture_path(char **store, const char *texture_path)
{
	char	*xpm;
	int		test_texture_fd;

	xpm = ft_strrchr(texture_path, '.');
	if (!xpm || ft_strncmp(xpm, ".xpm", 4))
		return (!cub3d_error("Invalid parse: Texture is not xpm file \"%s\"",
				texture_path));
	test_texture_fd = open(texture_path, O_RDONLY);
	if (test_texture_fd < 0)
		return (!cub3d_error("Invalid parse: Texture path invalid \"%s\"",
				texture_path));
	close(test_texture_fd);
	*store = ft_strdup(texture_path);
	if (!*store)
		return (!cub3d_error("Something unexpected"));
	return (true);
}

bool	parse_textures_paths(t_cub3d *app, char **data, size_t *index)
{
	char	*check_path;
	int		texture_id;

	while (*index < 4)
	{
		texture_id = get_texture_path_id(data[*index]);
		if (texture_id < 0)
		{
			if (texture_id == -1)
				break ;
			return (!cub3d_error("Invalid parse: "\
					"Line \"%s\" could not be recognised", data[*index]));
		}
		check_path = ft_strchr(data[*index], '.');
		if (!check_path)
			return (!cub3d_error("Invalid parse: No texture path found: \"%s\"",
					data[*index]));
		if (!store_texture_path(&app->texture_paths[texture_id], check_path))
			return (false);
		(*index)++;
	}
	if (*index != 4)
		return (!cub3d_error("Invalid parse: Required textures are missing"));
	return (true);
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

void	initialise(t_cub3d *app, const char *filepath)
{
	// (void)app;
	size_t		i;
	bool		success;
	t_fcontent	map_file;

	i = 0;
	ft_bzero(&map_file, sizeof(t_fcontent));
	success = read_file_contents(filepath, &map_file);
	success = success && parse_textures_paths(app, map_file.contents, &i);

	if (success)
	{
		ft_printf("------------------------------------------------------------\n");
		for (size_t j = 0; j < map_file.line_count && map_file.contents[j]; j++)
			ft_printf("%s\n", map_file.contents[j]);
		ft_printf("------------------------------------------------------------\n");

		ft_printf("------------------------------------------------------------\n");
		for (size_t j = 0; j < 4; j++)
			ft_printf("%s\n", app->texture_paths[j]);
		ft_printf("------------------------------------------------------------\n");
	}

	ft_free_str_2d(map_file.contents, map_file.line_count);

	destory_cub3d(app);
	
	if (!success)
		exit(1);

	ft_printf("Yay!!! You made it, well done!\n");
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
