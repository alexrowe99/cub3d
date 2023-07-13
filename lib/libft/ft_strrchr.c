/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 23:58:54 by lmells            #+#    #+#             */
/*   Updated: 2023/07/09 00:06:34 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	if (s[s_len] == (char)c)
		return (&((char *)s)[s_len]);
	while (s_len--)
	{
		if (s[s_len] == (char)c)
			return (&((char *)s)[s_len]);
	}
	return ((void *)0);
}
