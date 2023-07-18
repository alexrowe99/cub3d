/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:47:36 by lmells            #+#    #+#             */
/*   Updated: 2023/07/18 15:30:32 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc_gnl(size_t nmemb, size_t size)
{
	void	*block;
	size_t	bytes;

	bytes = nmemb * size;
	if (!bytes)
		return (NULL);
	block = malloc(bytes);
	if (!block)
		return (NULL);
	while (bytes--)
		((unsigned char *)block)[bytes] = 0;
	return (block);
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strndup_gnl(const char *s, size_t n)
{
	size_t	s_len;
	size_t	i;
	char	*dup;

	s_len = ft_strlen_gnl(s);
	if (n > s_len)
		n = s_len;
	dup = ft_calloc_gnl(n + 1, 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && i < n)
	{
		dup[i] = s[i];
		i++;
	}
	return (dup);
}

void	*ft_free_gnl(void **heap)
{
	free(*heap);
	*heap = NULL;
	return (NULL);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (&((char *)s)[i]);
		i++;
	}
	if (s[i] == c)
		return (&((char *)s)[i]);
	return (NULL);
}
