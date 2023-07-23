/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:39:26 by lmells            #+#    #+#             */
/*   Updated: 2023/07/23 16:46:26 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>

// Opens the file from filepath.
// Returns the file descriptor.
int	open_file(const char *filepath)
{
	return (open(filepath, O_RDONLY));
}

// Free... but with variadic arguments.
// The address of the pointer you would like to free are passed as variadic
// arguments.
void	vfree(size_t count, ...)
{
	void	**address;
	va_list	args;

	va_start(args, count);
	while (count--)
	{
		address = va_arg(args, void **);
		if (*address)
			free(*address);
		*address = NULL;
	}
	va_end(args);
}

char	**str_append2d(char **array, const char *s)
{
	ssize_t	i;
	ssize_t	array_len;
	char	**append;

	array_len = 0;
	if (array)
	{
		while (array[array_len])
			array_len++;
	}
	append = malloc((array_len + 2) * sizeof(char *));
	i = -1;
	if (append)
	{
		append[array_len + 1] = NULL;
		append[array_len] = ft_strdup(s);
		while (++i < array_len)
			append[i] = ft_strdup(array[i]);
	}
	while (array_len--)
		free(array[array_len]);
	free(array);
	return (append);
}
