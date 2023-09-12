/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:26:13 by lmells            #+#    #+#             */
/*   Updated: 2023/08/25 10:28:09 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_core.h>

int	ft_asprintf(char **ret, const char *fmt, ...)
{
	t_convert	c;

	ft_bzero(&c, sizeof(t_convert));
	c.buffer = ret;
	c.fp = (char *)fmt;
	va_start(c.args, fmt);
	printf_core(&c);
	va_end(c.args);
	return (c.ret_len);
}
