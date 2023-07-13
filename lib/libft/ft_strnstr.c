/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:54:49 by lmells            #+#    #+#             */
/*   Updated: 2023/07/09 13:10:48 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	char	c;
	char	sc;

	c = *needle++;
	if (c == '\0')
		return ((char *)haystack);
	needle_len = ft_strlen(needle);
	while (1)
	{
		while (1)
		{
			sc = *haystack;
			if (*haystack++ == '\0' || len-- < 1)
				return (NULL);
			if (sc == c)
				break ;
		}
		if (needle_len > len)
			return (NULL);
		if (ft_strncmp(haystack, needle, needle_len) == 0)
			break ;
	}
	haystack--;
	return ((char *)haystack);
}
