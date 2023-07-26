/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map_parser_textures.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:33:32 by lmells            #+#    #+#             */
/*   Updated: 2023/07/26 21:14:57 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	has_texture_header(const char *s)
{
	return (!ft_strncmp(s, "NO", 2) || !ft_strncmp(s, "SO", 2)
		|| !ft_strncmp(s, "EA", 2) || !ft_strncmp(s, "WE", 2));
}

t_texture_type	texture_type(char c)
{
	if (c == 'N')
		return (NORTH_WALL);
	if (c == 'S')
		return (SOUTH_WALL);
	if (c == 'E')
		return (EAST_WALL);
	if (c == 'W')
		return (WEST_WALL);
	return (COUNT_TEXTURE_TYPES);
}

bool	*validate_texture_paths(size_t *row_offset, t_map **data,
	t_validation *validation)
{
	size_t	i;
	char	*extension;

	if (*row_offset != COUNT_TEXTURE_TYPES)
		return (&(add_validation_error(validation,
					ERR_PARSE_MAP" : missing texture(s).")->caught_error));
	i = COUNT_TEXTURE_TYPES;
	while (!validation->caught_error && i--)
	{
		if (!(*data)->texture_paths[i][2])
		{
			add_validation_error(validation,
				ERR_PARSE_MAP" : path to texture is empty.");
			break;
		}
		extension = ft_strrchr(&(*data)->texture_paths[i][2], '.');
		if (!extension || ft_strncmp(extension, ".xpm", 4))
		{
			add_validation_error(validation,
				ERR_PARSE_MAP" : invalid texture file... must be '.xpm'.");
			break ;
		}
	}
	return (&validation->caught_error);
}
