/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map_initialiser.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:27:12 by lmells            #+#    #+#             */
/*   Updated: 2023/07/19 20:40:15 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>

static void	*read_map_file(const char *filepath, t_map **data)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (print_error("Failed to open file."));

	if (DEBUG)
		printf("============= File Contents =============\n");

	size_t	width = 0;
	size_t	expected[2] = {0};
	for (char *raw = get_next_line(fd); raw; raw = get_next_line(fd))
	{
		char *line = ft_strtrim(raw, "\n");
		bool line_is_parseable = line && *line != 0;
		if (DEBUG)
		{
			printf("%s\n", line);
			if (line_is_parseable && *line == '#')
			{
				char *expected_value = ft_strchr(line, ':') - 5;
				if (*expected_value == 'W')
					expected[0] = ft_atoi(expected_value + 6);
				else
				{
					expected_value = ft_strchr(line, ':') - 6;
					if (*expected_value == 'H')
						expected[1] = ft_atoi(expected_value + 7);
				}
			}
		}
		if (line_is_parseable && *line != '#')
		{
			width = ft_strlen(line);
			if ((*data)->m_width < width)
				(*data)->m_width = width;
			(*data)->m_height++;
		}
		if (line)
			free(line);
		free(raw);
	}
	close(fd);

	// Compare width and height results here.
	bool valid = expected[0] == (*data)->m_width
		&& expected[1] == (*data)->m_height;
	if (DEBUG)
	{
		printf("=========================================\n");
		if (!valid)
		{
			printf("Expected Map Width: %zu; Read Map Width: %zu;\n",
				expected[0], (*data)->m_width);
			printf("Expected Map Height: %zu; Read Map Height: %zu;\n",
				expected[1], (*data)->m_height);
		}
		else
			printf("Map dimensions were read successfully\n");
		printf("=========================================\n");
	}

	if (!valid)
		return (print_error("Invalid map."));
	return (*data);
}

t_map	*initialise_map_data(const char *map_filepath, t_map **data)
{
	*data = ft_calloc(1, sizeof(t_map));
	if (!*data)
		return (print_error(__ERR_MEM_ALLOC_FAIL__));
	if (!read_map_file(map_filepath, data))
		return (print_error("Failed to initialise map data."));
	return (*data);
}
