/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:10:50 by lmells            #+#    #+#             */
/*   Updated: 2023/08/13 15:09:47 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftall.h"
#include <stdlib.h>

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*join_str;
	char	*join_p;
	size_t	s2_len;
	size_t	s1_len;

	s2_len = ft_strlen(s2);
	if (!s2_len)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	join_str = malloc(s1_len + s2_len + 1);
	if (!join_str)
		return (NULL);
	join_p = join_str;
	if (s1)
	{
		while (s1_len--)
			*join_p++ = *s1++;
	}
	while (s2_len--)
		*join_p++ = *s2++;
	*join_p = '\0';
	return (join_str);
}
