/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:24:07 by lmells            #+#    #+#             */
/*   Updated: 2023/07/28 00:18:07 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_error.h"
#include "libft.h"

void	*print_error(const char *message)
{
	const char	*prefix;
	size_t		prefix_len;
	char		buffer[MAX_BUFFER];

	prefix = TEXT_RED "Error\n" TEXT_WHITE;
	prefix_len = ft_strlen(prefix);
	ft_bzero(buffer, MAX_BUFFER);
	ft_memcpy(buffer, prefix, prefix_len);
	ft_memcpy(&buffer[prefix_len], message, ft_strlen(message));
	buffer[MAX_BUFFER - 1] = '\0';
	write(STDERR_FILENO, buffer, ft_strlen(buffer));
	write(STDERR_FILENO, "\n", 1);
	return (NULL);
}
