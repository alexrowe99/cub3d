/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:24:07 by lmells            #+#    #+#             */
/*   Updated: 2023/07/23 13:49:58 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_error.h"
#include "libft.h"

void	*print_error(const char *message)
{
	const char	*prefix;
	size_t		prefix_len;
	const char	*seperator;
	size_t		seperator_len;
	char		buffer[MAX_BUFFER];

	prefix = TEXT_RED "Error";
	prefix_len = ft_strlen(prefix);
	seperator = TEXT_WHITE " : ";
	seperator_len = ft_strlen(seperator);
	ft_bzero(buffer, MAX_BUFFER);
	ft_memcpy(buffer, prefix, prefix_len);
	ft_memcpy(&buffer[prefix_len], seperator, seperator_len);
	ft_memcpy(&buffer[prefix_len + seperator_len], message, ft_strlen(message));
	buffer[MAX_BUFFER - 1] = '\0';
	write(STDERR_FILENO, buffer, ft_strlen(buffer));
	write(STDERR_FILENO, "\n", 1);
	return (NULL);
}
