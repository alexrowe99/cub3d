/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:47:54 by lmells            #+#    #+#             */
/*   Updated: 2023/07/23 17:02:13 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

enum e_parser_actions
{
	READ = 0,
	PROCESS,
	COUNT_PARSER_ACTIONS
};

typedef struct s_map_parser
{
	char		*line[COUNT_PARSER_ACTIONS];
	bool		(*process_line)(const char *, t_map **data,
		t_validator	*validation);
	t_validator	validation;
}	t_parser;

// Generic method that processes each line in the specified file using the 
// function provided by the function pointer 'process_line'.
// The 'process_line' handler will be given a pointer to the address of where 
// map data is stored. It is up to the handler to set map data values.
t_validator	read_map_file(int map_fd, t_map **data, t_parser *parser,
	bool (*process_line)(const char *, t_map **, t_validator *validation))
{
	if (map_fd < 0)
	{
		add_validation_error(&parser->validation,
			__ERR_MAP_INIT_FAIL__" : Could not open map file.");
		parser->validation.success = false;
		return (parser->validation);
	}
	parser->line[READ] = get_next_line(map_fd);
	while (parser->validation.success && parser->line[READ])
	{
		parser->line[PROCESS] = ft_strtrim(parser->line[READ], "\n");
		parser->validation.success = process_line(parser->line[PROCESS], data,
				&parser->validation);
		vfree(2, &parser->line[READ], &parser->line[PROCESS]);
		parser->line[READ] = get_next_line(map_fd);
	}
	close(map_fd);
	return (parser->validation);
}

// Simply updates the map's width & height dimensions.
// Width is only updated if line length is greater than one stored in data.
// Will always return true as process cannot fail.
static bool	save_map_dimensions(const char *process_line, t_map **data,
	t_validator *validation)
{
	size_t	width;

	width = 0;
	if (*process_line == '1' || *process_line == ' ')
	{
		width = ft_strlen(process_line);
		if ((*data)->m_width < width)
			(*data)->m_width = width;
		(*data)->m_height++;
	}
	else
	{
		validation = add_validation_error(validation,
				__ERR_MAP_INIT_FAIL__" : Could not process line.");
		return (false);
	}
	return (true);
}

static bool	populate_map_tiles(const char *process_line, t_map **data,
	t_validator *validation)
{
	static size_t	y;
	ssize_t			x;
	char			c;

	if (!process_line)
		return (add_validation_error(validation,
				__ERR_MAP_POPTILE_FAIL__" : no line to process.")->success);
	(*data)->tiles = str_append2d((*data)->tiles, process_line);
	if (!(*data)->tiles)
		return (add_validation_error(validation,
				__ERR_MAP_POPTILE_FAIL__" : "__MEM_ALLOC__)->success);
	x = -1;
	while ((*data)->tiles[y][++x] != '\0')
	{
		c = (*data)->tiles[y][x];
		if (!(c == ' ' || c == '0' || c == '1' || c == 'N' || c == 'S'
				|| c == 'E' || c == 'W'))
		{
			(*data)->m_height = y + 1;
			return (add_validation_error(validation,
					__ERR_MAP_POPTILE_FAIL__" : "__MAP_INVALID__)->success);
		}
	}
	y++;
	return (validation->success);
}

void	parser_exit(t_validator *validation, t_map **data)
{
	size_t	i;

	i = 0;
	if (!validation->success && validation->error_count)
	{
		while (i < validation->error_count)
			print_error(validation->error_messages[i++]);
	}
	free_validator(validation);
	exit_free(data);
}

void	parse_map_file(const char *filepath, t_map **data)
{
	t_parser	parser;

	ft_bzero(&parser, sizeof(t_parser));
	parser.validation.success = true;
	read_map_file(open_file(filepath), data, &parser, save_map_dimensions);
	read_map_file(open_file(filepath), data, &parser, populate_map_tiles);
	if (!parser.validation.success)
		parser_exit(&parser.validation, data);
	free_validator(&parser.validation);
}
