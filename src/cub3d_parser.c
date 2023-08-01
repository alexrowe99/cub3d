/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:33:32 by lmells            #+#    #+#             */
/*   Updated: 2023/07/28 17:59:08 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_initialiser	*parse_map_data(t_file *map_file, t_map **data,
	t_initialiser *init)
{
	t_parse	information;
	size_t	row_offset;
	void	(*parse[COUNT_PARSER_FUNCTIONS])(char **, size_t *, t_map **,
			t_initialiser *);

	ft_bzero(parse, sizeof(void *) * COUNT_PARSER_FUNCTIONS);
	parse[TEXTURE_PATHS] = parse_wall_texture_path;
	parse[FC_RGB_VALUES] = parse_floor_ceiling_rgb_values;
	parse[MAP_TILES] = parse_map_tiles;
	information = TEXTURE_PATHS;
	row_offset = 0;
	init->error = &init->validation.caught_error;
	while (!*init->error && information < COUNT_PARSER_FUNCTIONS)
		parse[information++](map_file->data, &row_offset, data, init);
	free_file_data(&map_file);
	return (init);
}

void	parse_wall_texture_path(char **info, size_t *row_offset, t_map **data,
	t_initialiser *init)
{
	ssize_t	i;

	i = -1;
	while (++i < COUNT_TEXTURE_TYPES)
	{
		if (!*info[*row_offset] || !has_texture_header(info[*row_offset]))
		{
			init->error = &(add_validation_error(&init->validation,
						ERR_INIT_MAP" : "ERR_PARSE_MAP" : line in file is "\
						"unrecognisable.")->caught_error);
			return ;
		}
		save_texture_path(info[(*row_offset)++], (*data)->texture_paths, init);
		if (*init->error)
			return ;
	}
	init->error = validate_texture_paths(row_offset, data, &init->validation);
}

void	parse_floor_ceiling_rgb_values(char **info, size_t *row_offset,
	t_map **data, t_initialiser *init)
{
	ssize_t	i;
	size_t	store;
	char	*rgb_value_str;

	i = -1;
	ft_bzero((*data)->rgb, sizeof(t_rgb) * COUNT_RGB_PARSE);
	while (++i < COUNT_RGB_PARSE)
	{
		rgb_value_str = ft_strtrim(&info[*row_offset][1], "\t ");
		store = rgb_store_index(*info[*row_offset]);
		if (!ft_isdigit(*rgb_value_str) || store == COUNT_RGB_PARSE)
		{
			free(rgb_value_str);
			init->error = &(add_validation_error(&init->validation,
						ERR_INIT_MAP" : "ERR_PARSE_MAP" : "ERR_RGB_PARSE" : "\
						UNKOWN_CHAR)->caught_error);
			return ;
		}
		parse_rgb_value(rgb_value_str, &(*data)->rgb[store], init);
		free(rgb_value_str);
		if (*init->error)
			return ;
		(*row_offset)++;
	}
	init->error = validate_rgb_range((*data)->rgb, init)->error;
}

void	parse_map_tiles(char **info, size_t *row_offset, t_map **data,
	t_initialiser *init)
{
	if (*get_map_dimensions(info, *row_offset, data, init)->error)
		return ;
	(*data)->tiles = alloc_map_tiles((*data)->map_height, (*data)->map_height);
	if (!(*data)->tiles)
	{
		init->error = &(add_validation_error(&init->validation,
					ERR_INIT_MAP" : "ERR_PARSE_MAP" : "\
					MEM_ALLOC)->caught_error);
		return ;
	}
	if (*populate_map_tiles(info, row_offset, data, init)->error)
		return ;
	floodfill_map_validation(data, init);
}
