/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:47:54 by lmells            #+#    #+#             */
/*   Updated: 2023/07/20 20:41:21 by lmells           ###   ########.fr       */
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
	bool		(*process_line)(const char *, t_map **data);
	t_validator	validation;
}	t_parser;

// Generic method that processes each line in the specified file using the 
// function provided by the function pointer 'process_line'.
// The 'process_line' handler will be given a pointer to the address of where 
// map data is stored. It is up to the handler to set map data values.
t_validator	read_map_file(int map_fd, t_map **data, t_parser *parser,
	bool (*process_line)(const char *, t_map **))
{
	if (map_fd < 0)
	{
		parser->validation.success = false;
		return (parser->validation);
	}
	parser->line[READ] = get_next_line(map_fd);
	while (parser->line[READ])
	{
		parser->line[PROCESS] = ft_strtrim(parser->line[READ], "\n");
		parser->validation.success = process_line(parser->line[PROCESS], data);
		vfree(2, &parser->line[READ], &parser->line[PROCESS]);
		parser->line[READ] = get_next_line(map_fd);
	}
	close(map_fd);
	return (parser->validation);
}

// Simply updates the map's width & height dimensions.
// Width is only updated if line length is greater than one stored in data.
// Will always return true as process cannot fail.
static bool	save_map_dimensions(const char *process_line, t_map **data)
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
	return (true);
}

void	parse_map_file(const char *filepath, t_map **data)
{
	t_parser	parser;

	ft_bzero(&parser, sizeof(t_parser));
	read_map_file(open_file(filepath), data, &parser, save_map_dimensions);
	if (!parser.validation.success)
	{
		free_validator(&parser.validation);
		exit_free(data);
	}
		// validation_failed_exit_free(&parser.validation, data);
	// validate_map_tiles(open_file(filepath), data, &parser);
	// if (!parser.validation.success)
	// 	validation_failed_exit_free(&parser.validation, data);
	free_validator(&parser.validation);
}
