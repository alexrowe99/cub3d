/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:08:25 by lmells            #+#    #+#             */
/*   Updated: 2023/07/09 16:12:42 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*alloc;
	size_t	bytes;

	bytes = count * size;
	alloc = malloc(bytes);
	if (!alloc)
		return ((void *)0);
	return (ft_memset(alloc, 0, bytes));
}
