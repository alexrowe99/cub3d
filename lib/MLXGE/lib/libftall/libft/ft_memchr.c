/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:41:43 by lmells            #+#    #+#             */
/*   Updated: 2023/07/09 11:50:53 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;

	if (!n)
		return ((void *)0);
	p = (unsigned char *)s;
	while (--n)
	{
		if (*p == (unsigned char)c)
			return ((void *)p);
		p++;
	}
	if (*p == (unsigned char)c)
		return ((void *)p);
	return ((void *)0);
}
