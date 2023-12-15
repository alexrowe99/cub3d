/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_textures_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:52:57 by lmells            #+#    #+#             */
/*   Updated: 2023/12/12 14:39:30 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bonus/cub3d_bonus.h>

int	get_texture_id(const char *element)
{
	int	texture_id;

	texture_id = -1;
	if (!ft_strncmp(element, "NO", 2))
		texture_id = 0;
	else if (!ft_strncmp(element, "SO", 2))
		texture_id = 1;
	else if (!ft_strncmp(element, "EA", 2))
		texture_id = 2;
	else if (!ft_strncmp(element, "WE", 2))
		texture_id = 3;
	return (texture_id);
}

static char	*validate_texture_path(const char *line)
{
	char	*texture_path;
	char	*xpm;
	int		test_texture_fd;

	texture_path = ft_strchr(line, '.');
	if (!texture_path)
	{
		cub3d_error("Invalid parse: No texture path found: \"%s\"", line);
		return (NULL);
	}
	xpm = ft_strrchr(texture_path, '.');
	if (!xpm || ft_strncmp(xpm, ".xpm", 4))
	{
		cub3d_error("Invalid parse: Texture is not xpm file \"%s\"", line);
		return (NULL);
	}
	test_texture_fd = open(texture_path, O_RDONLY);
	if (test_texture_fd < 0)
	{
		cub3d_error("Invalid parse: Texture path invalid \"%s\"", line);
		return (NULL);
	}
	close(test_texture_fd);
	return (texture_path);
}

bool	store_xpm_path(char **store_path, const char *valid_path)
{
	if (!valid_path)
		return (false);
	*store_path = ft_strdup(valid_path);
	if (!*store_path)
		return (!cub3d_error("Something unexpected happened"));
	return (true);
}

bool	parse_texture_element(const char *element, size_t elem_id, t_cub3d *app)
{
	bool	valid;
	char	*path;

	if (app->wall_texture_paths[elem_id])
		return (!cub3d_error("Invalid parse: Duplicate texture found "\
				"\"%s\"", element));
	path = ft_strtrim(&element[2], " \t");
	if (!*path)
	{
		free(path);
		return (!cub3d_error("Invalid parse: No texture path found: \"%s\"",
				element));
	}
	valid = store_xpm_path(&app->wall_texture_paths[elem_id],
			validate_texture_path(path));
	free(path);
	return (valid);
}
