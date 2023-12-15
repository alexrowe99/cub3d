/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:37:07 by lmells            #+#    #+#             */
/*   Updated: 2023/12/12 14:39:34 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bonus/cub3d_bonus.h>

static bool	get_file_contents(const char *filepath, t_file *file)
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

static bool	check_data_populated(t_cub3d *app, bool validated)
{
	size_t	i;

	if (!validated)
		return (false);
	i = 0;
	while (i < TEXTURE_COUNT)
	{
		if (app->wall_texture_paths[i++] == NULL)
			return (!cub3d_error("Invalid parse: Required texture paths are "\
					"missing"));
	}
	return (true);
}

static bool	parse_map_settings(t_file *file, t_cub3d *app)
{
	int		id;
	bool	valid;

	valid = true;
	while (file->it != file->line_count)
	{
		id = get_texture_id(file->contents[file->it]);
		valid = id >= 0 && parse_texture_element(file->contents[file->it],
				id, app);
		if (!valid && id < 0)
		{
			id = get_rgb_id(file->contents[file->it]);
			valid = id >= 0 && parse_rgb_element(file->contents[file->it],
					id, app);
		}
		if (!valid)
			break ;
		file->it++;
	}
	if (id == -1 && file->it != COUNT_ELEMENTS
		&& file->it != file->line_count)
		return (!cub3d_error("Invalid parse: Line \"%s\" is not recognisable",
				file->contents[file->it]));
	return (check_data_populated(app, valid || file->it == COUNT_ELEMENTS));
}

bool	parse_map_file(t_cub3d *app, const char *filepath)
{
	bool	success;
	t_file	file;

	errno = 0;
	ft_bzero(&file, sizeof(file));
	success = get_file_contents(filepath, &file);
	success = success && parse_map_settings(&file, app);
	success = success && parse_map_tiles(&file, &app->world);
	ft_free_str_2d(file.contents, file.line_count);
	return (success);
}
