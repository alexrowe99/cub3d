/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 22:59:51 by lmells            #+#    #+#             */
/*   Updated: 2023/07/08 23:01:35 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*p;

	if (!dst && !src)
		return (dst);
	p = (unsigned char *)dst;
	while (n--)
		*p++ = *(unsigned char *)src++;
	return (dst);
}
