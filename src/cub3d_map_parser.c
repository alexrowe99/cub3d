/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:33:32 by lmells            #+#    #+#             */
/*   Updated: 2023/07/26 17:52:21 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>

// FC - Floor & Ceiling.

typedef enum e_parser_functions
{
	TEXTURE_PATHS,
	FC_RGB_VALUES,
	MAP_TILES,
	COUNT_PARSER_FUNCTIONS
}	t_parse;

// Texture Parser

static bool	has_texture_header(const char *s)
{
	return (!ft_strncmp(s, "NO", 2) || !ft_strncmp(s, "SO", 2)
		|| !ft_strncmp(s, "EA", 2) || !ft_strncmp(s, "WE", 2));
}

static t_texture_type	texture_type(char c)
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

static bool	*validate_texture_paths(size_t *row_offset, t_map **data,
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

// 	- Store paths to texture sprites.
// 	- Store rgb values for floor and ceiling colours.
void	parse_wall_texture_path(char **info, size_t *row_offset, t_map **data,
	t_initialiser *init)
{
	ssize_t			i;
	char			*info_line;
	char			*path;

	i = -1;
	while (++i < COUNT_TEXTURE_TYPES)
	{
		path = NULL;
		info_line = ft_strtrim(info[*row_offset], "\t ");
		if (*info_line && has_texture_header(info_line))
		{
			path = ft_strtrim(&info_line[2], "\t ");
			if (!path || !*path)
			{
				vfree(2, &info_line, &path);
				init->error = &(add_validation_error(&init->validation,
							ERR_PARSE_MAP" : could not find any path for \
texture.")->caught_error);
				return ;
			}
			(*data)->texture_paths[texture_type(*info_line)] = ft_strdup(path);
			(*row_offset)++;
		}
		vfree(2, &info_line, &path);
	}
	init->error = validate_texture_paths(row_offset, data, &init->validation);
}

// void	parse_floor_ceiling_rgb_values(char **info, size_t *row_offset,
// 	t_map **data, t_initialiser *init)
// {

// }

// void	parse_map_tile_characters(char **info, size_t *row_offset,
// 	t_map **data, t_initialiser *init)
// {

// }

t_initialiser	*parse_map_data(t_file *map_file, t_map **data,
	t_initialiser *init)
{
	t_parse	information;
	size_t	row_offset;
	void	(*parse[COUNT_PARSER_FUNCTIONS])(char **, size_t *, t_map **,
			t_initialiser *);

	parse[TEXTURE_PATHS] = parse_wall_texture_path;
	// parse[FC_RGB_VALUES] = parse_floor_ceiling_rgb_values;
	// parse[MAP_TILES] = parse_map_tile_characters;
	information = TEXTURE_PATHS;
	row_offset = 0;
	init->error = &init->validation.caught_error;
	while (!*init->error && information < COUNT_PARSER_FUNCTIONS)
		parse[information++](map_file->data, &row_offset, data, init);
	free_file_data(&map_file);
	return (init);
}
