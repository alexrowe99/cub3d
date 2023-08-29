/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:26:33 by lmells            #+#    #+#             */
/*   Updated: 2023/08/13 15:29:12 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftall.h>

char	*ft_strndup(const char *s, size_t n)
{
	size_t	s_len;
	char	*dup;

	s_len = ft_strlen(s);
	if (n > s_len)
		n = s_len;
	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	dup[n] = '\0';
	while (n--)
		dup[n] = s[n];
	return (dup);
}
