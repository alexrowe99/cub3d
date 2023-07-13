/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arowe <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:58:45 by arowe             #+#    #+#             */
/*   Updated: 2021/10/08 12:58:45 by arowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	ctr;
	int		diff;

	ctr = 0;
	while (ctr < n && !(s1[ctr] == '\0' && s2[ctr] == '\0'))
	{
		if (s1[ctr] != s2[ctr])
		{
			diff = (unsigned char)s1[ctr] - (unsigned char)s2[ctr];
			return (diff);
		}
		ctr++;
	}
	return (0);
}
