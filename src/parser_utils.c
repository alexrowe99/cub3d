/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:32:26 by lmells            #+#    #+#             */
/*   Updated: 2023/09/07 12:33:57 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	is_spawn_tile(int c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	is_valid_character(int c)
{
	return (c == ' ' || c == '0' || c == '1' || is_spawn_tile(c));
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
