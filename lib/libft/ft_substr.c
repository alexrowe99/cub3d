/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:40:32 by lmells            #+#    #+#             */
/*   Updated: 2023/07/12 16:14:13 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
