/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arowe <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:58:45 by arowe             #+#    #+#             */
/*   Updated: 2021/10/08 12:58:45 by arowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	index_src;
	size_t	index_dest;
	size_t	dest_len;

	index_dest = 0;
	index_src = 0;
	while (dest[index_dest])
		index_dest++;
	dest_len = index_dest;
	if (size > dest_len)
	{
		while (index_src < (size - dest_len - 1) && src[index_src])
		{
			dest[index_dest++] = src[index_src++];
		}
		dest[index_dest] = '\0';
	}
	while (src[index_src])
	{
		index_src++;
		index_dest++;
	}
	if (size >= dest_len)
		return (index_dest);
	return (index_src + size);
}
