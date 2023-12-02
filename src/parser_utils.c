/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:32:26 by lmells            #+#    #+#             */
/*   Updated: 2023/12/02 16:39:46 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	is_spawn_tile(int c, t_entity *entity)
{
	bool	is_spawn;

	is_spawn = c == 'N' || c == 'S' || c == 'E' || c == 'W';
	if (entity && is_spawn)
	{
		if (c == 'N')
			entity->direction = (t_v2d){0, -1};
		else if (c == 'S')
			entity->direction = (t_v2d){0, 1};
		else if (c == 'E')
			entity->direction = (t_v2d){-1, 0};
		else if (c == 'W')
			entity->direction = (t_v2d){1, 0};
	}
	return (is_spawn);
}

bool	is_valid_character(int c)
{
	return (c == ' ' || c == '0' || c == '1' || is_spawn_tile(c, 0));
}

bool	validate_map_tiles(const char *line)
{
	while (*line != '\0')
	{
		if (!is_valid_character(*line))
			return (!cub3d_error("Invalid parse: Line \"%s\" contains invalid "\
					"character - ASCII '%i'", line, *line));
		line++;
	}
	return (true);
}

int	store_tile(char tile)
{
	char	tile_p[1];

	*tile_p = tile;
	if (tile != ' ')
	{
		if (is_spawn_tile(tile, 0))
			return (tile);
		return (ft_atoi(tile_p) + 1);
	}
	return (-1);
}
