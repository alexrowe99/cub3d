/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 23:03:03 by lmells            #+#    #+#             */
/*   Updated: 2023/08/13 15:09:47 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftall.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*p;

	if (!dst && !src)
		return (dst);
	p = (unsigned char *)dst;
	if (src < dst)
	{
		while (len--)
			p[len] = ((unsigned char *)src)[len];
	}
	else
	{
		while (len--)
			*p++ = *(unsigned char *)src++;
	}
	return (dst);
}
