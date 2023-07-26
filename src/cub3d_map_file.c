/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:53:50 by lmells            #+#    #+#             */
/*   Updated: 2023/07/25 12:50:04 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>

void	*free_file_data(t_file **file)
{
	if (!*file)
		return (NULL);
	if ((*file)->data)
	{
		while ((*file)->line_count--)
			free((*file)->data[(*file)->line_count]);
		free((*file)->data);
	}
	free(*file);
	*file = NULL;
	return (NULL);
}

static t_file	*populate_file_contents(t_file *file, int map_fd,
	t_initialiser *init)
{
	char	*line;
	char	*information;

	line = get_next_line(map_fd);
	while (line)
	{
		information = ft_strtrim(line, "\n");
		if (*information)
		{
			file->line_count++;
			file->data = str_append2d(file->data, information);
			if (!file->data)
			{
				close(map_fd);
				init->error = &(add_validation_error(&init->validation,
				ERR_INIT_MAP" : "MEM_ALLOC)->caught_error);
				return (free_file_data(&file));
			}
		}
		vfree(2, &line, &information);
		line = get_next_line(map_fd);
	}
	close(map_fd);
	return (file);
}

t_file	*get_map_file_contents(const char *filepath, t_initialiser *init)
{
	int		map_fd;
	t_file	*file;

	map_fd = open(filepath, O_RDONLY);
	if (map_fd < 0)
	{
		init->error = &(add_validation_error(&init->validation,
			"Could not open file : invalid file descriptor.")->caught_error);
		return (NULL);
	}
	file = ft_calloc(1, sizeof(t_file));
	if (!file)
	{
		init->error = &(add_validation_error(&init->validation,
			ERR_INIT_MAP" : "MEM_ALLOC)->caught_error);
		return (NULL);
	}
	return (populate_file_contents(file, map_fd, init));
}
