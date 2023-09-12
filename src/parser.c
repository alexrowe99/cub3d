/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:37:07 by lmells            #+#    #+#             */
/*   Updated: 2023/09/08 14:11:40 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

static bool	check_data_populated(t_cub3d *app, bool validated)
{
	size_t	i;

	if (!validated)
		return (false);
	i = 0;
	while (i < TEXTURE_COUNT)
	{
		if (app->texture_paths[i++] == NULL)
			return (!cub3d_error("Invalid parse: Required texture paths are "\
					"missing"));
	}
	i = 0;
	while (i < RGB_COUNT)
	{
		if (app->rgb_floor_ceiling[i++] == NULL)
			return (!cub3d_error("Invalid parse: Required RGB values are "\
					"missing"));
	}
	return (true);
}

static bool	parse_map_settings(t_file *m_file, t_cub3d *app)
{
	int		id;
	bool	valid;

	valid = true;
	while (m_file->it != m_file->line_count)
	{
		id = get_texture_id(m_file->contents[m_file->it]);
		valid = id >= 0 && parse_texture_element(m_file->contents[m_file->it],
				id, app);
		if (!valid && id < 0)
		{
			id = get_rgb_id(m_file->contents[m_file->it]);
			valid = id >= 0 && parse_rgb_element(m_file->contents[m_file->it],
					id, app);
		}
		if (!valid)
			break ;
		m_file->it++;
	}
	if (id == -1 && m_file->it != COUNT_ELEMENTS
		&& m_file->it != m_file->line_count)
		return (!cub3d_error("Invalid parse: Line \"%s\" is not recognisable",
				m_file->contents[m_file->it]));
	return (check_data_populated(app, valid || m_file->it == COUNT_ELEMENTS));
}

void	parse_map_file(t_cub3d *app, const char *filepath)
{
	bool	success;
	t_file	map_file;

	errno = 0;
	ft_bzero(&map_file, sizeof(t_file));
	success = read_file_contents(filepath, &map_file);
	success = success && parse_map_settings(&map_file, app);
	success = success && parse_map_tiles(&map_file, app);
	ft_free_str_2d(map_file.contents, map_file.line_count);
	if (!success)
	{
		destory_cub3d(app);
		exit(1);
	}
}
