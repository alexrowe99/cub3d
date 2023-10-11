/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vfree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:07:10 by lmells            #+#    #+#             */
/*   Updated: 2023/08/29 18:13:10 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>

void	*ft_vfree(size_t count, ...)
{
	va_list	argp;
	void	**addr;

	va_start(argp, count);
	while (count--)
	{
		addr = va_arg(argp, void **);
		if (*addr)
			free(*addr);
		*addr = NULL;
	}
	va_end(argp);
	return (NULL);
}
