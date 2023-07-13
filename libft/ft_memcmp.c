/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arowe <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:58:44 by arowe             #+#    #+#             */
/*   Updated: 2021/10/08 12:58:44 by arowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				ctr;
	int					diff;
	int					c;
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = s1;
	str2 = s2;
	ctr = 0;
	while (ctr < n)
	{
		if (str1[ctr] != str2[ctr])
		{
			c = str1[ctr];
			if (c < 0)
				c *= -1;
			diff = c - str2[ctr];
			return (diff);
		}
		ctr++;
	}
	return (0);
}
