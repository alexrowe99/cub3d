/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arowe <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:58:44 by arowe             #+#    #+#             */
/*   Updated: 2021/10/08 12:58:44 by arowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int	i;

	if (dest > src)
	{
		i = (int)n - 1;
		while (i >= 0)
		{
			*((char *)(dest + i)) = *((char *)(src + i));
			i--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
