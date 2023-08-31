/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:52:57 by lmells            #+#    #+#             */
/*   Updated: 2023/08/31 19:06:21 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	get_texture_path_id(const char *texture_info)
{
	int	texture_id;

	texture_id = -1;
	if (!ft_strncmp(texture_info, "NO", 2))
		texture_id = 0;
	else if (!ft_strncmp(texture_info, "SO", 2))
		texture_id = 1;
	else if (!ft_strncmp(texture_info, "EA", 2))
		texture_id = 2;
	else if (!ft_strncmp(texture_info, "WE", 2))
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

static bool	store_texture_path(char **store, const char *texture_path)
{
	if (!texture_path)
		return (false);
	*store = ft_strdup(texture_path);
	if (!*store)
		return (!cub3d_error("Something unexpected happened"));
	return (true);
}

bool	parse_textures_paths(t_file *map, t_cub3d *app, size_t texture_count)
{
	int		texture_id;

	while (map->it < TEXTURE_COUNT && map->contents[map->it])
	{
		texture_id = get_texture_path_id(map->contents[map->it]);
		if (texture_id < 0)
			return (!cub3d_error("Invalid parse: Unrecognisable texture "\
					"setting \"%s\"", map->contents[map->it]));
		if (app->texture_paths[texture_id])
			return (!cub3d_error("Invalid parse: Duplicate texture found "\
					"\"%s\"", map->contents[map->it]));
		if (!store_texture_path(&app->texture_paths[texture_id],
				validate_texture_path(map->contents[map->it])))
			return (false);
		map->it++;
	}
	while (map->it--)
		if (!app->texture_paths[map->it])
			return (!cub3d_error("Invalid parse: Required textures are "\
					"missing"));
	map->it = texture_count;
	return (true);
}
