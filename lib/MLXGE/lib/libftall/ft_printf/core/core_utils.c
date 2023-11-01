/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:27:48 by lmells            #+#    #+#             */
/*   Updated: 2023/10/30 11:57:19 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_core.h>

size_t	get_unsigned_len_base(uint64_t n, size_t base)
{
	size_t	i;

	if (!n)
		return (1);
	i = 0;
	while (n)
	{
		i++;
		n /= base;
	}
	return (i);
}

#define BUFFER_RESIZE 64

void	*init_buffer(t_convert *c)
{
	c->bs = BUFFER_RESIZE;
	*c->buffer = malloc(c->bs + 1);
	if (!*c->buffer)
	{
		c->ret_len = -1;
		*c->buffer = NULL;
	}
	return (*c->buffer);
}

int	resize_buffer(t_convert *c)
{
	c->bs = ft_resize_str(c->buffer, c->bs + BUFFER_RESIZE);
	if (c->bs == -1)
		return (-1);
	return (c->ret_len);
}

int	conversion_failure(t_convert *c)
{
	free(*c->buffer);
	*c->buffer = NULL;
	c->ret_len = -1;
	return (CONVERT_FAIL);
}
