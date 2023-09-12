/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:40:32 by lmells            #+#    #+#             */
/*   Updated: 2023/08/13 15:09:47 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftall.h"

char	*ft_substr(const char *s, size_t start, size_t len)
{
	const char	*p;
	char		*sub;

	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	p = &s[start];
	while (*p != '\0' && len--)
		p++;
	len = p - (s + start);
	sub = malloc(len + 1);
	if (!sub)
		return ((void *)0);
	sub[len] = '\0';
	return (ft_memcpy(sub, s + start, len));
}
