/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:13:38 by lmells            #+#    #+#             */
/*   Updated: 2023/08/13 15:09:47 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftall.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s1);
	dup = malloc(len + 1);
	if (!dup)
		return ((void *)0);
	dup[len] = '\0';
	while (len--)
		dup[len] = s1[len];
	return (dup);
}
