/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:10:53 by lmells            #+#    #+#             */
/*   Updated: 2023/08/28 22:39:31 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <fcntl.h>

bool	cub3d_error(const char *message)
{
	ft_printf("\e[0;91mError\e[0m\n%s\n", message);
	return (false);
}

static bool	validate_args(int ac, char **av)
{
	char	*ext;

	if (ac != 2)
		return (cub3d_error("Incorrect number of arguments"));
	ext = ft_strrchr(av[1], '.');
	if (!ext || ft_strncmp(".cub", ext, 4))
		return (cub3d_error("Argument is not a .cub map file"));
	return (true);
}

static void	read_file_contents(const char *filepath, t_fcontent *file)
{
	file->fd = open(filepath, O_RDONLY);
	if (file->fd < 0)
	{
		cub3d_error("Could not open file");
		exit(1);
	}
	for (char *line = get_next_line(file->fd); line; line = get_next_line(file->fd))
	{
		file->contents = ft_append_str_2d(file->contents, line);
		if (!file->contents)
		{
			cub3d_error("Could not read map file-> malloc failure");
			exit(1);
		}
		file->line_count++;
		free(line);
	}
	close(file->fd);
}

void	initialise(t_cub3d *app, const char *filepath)
{
	(void)app;
	t_fcontent	map_file;

	read_file_contents(filepath, &map_file);
	for (size_t i = 0; i < map_file.line_count && map_file.contents[i]; i++)
		ft_printf("%s", map_file.contents[i]);

	ft_free_str_2d(map_file.contents, map_file.line_count);
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
