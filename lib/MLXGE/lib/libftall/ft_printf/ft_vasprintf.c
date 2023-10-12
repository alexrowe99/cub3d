/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vasprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 11:04:03 by lmells            #+#    #+#             */
/*   Updated: 2023/08/25 10:25:43 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_core.h>

int	ft_vasprintf(char **ret, const char *format, va_list args)
{
	t_convert	c;

	ft_bzero(&c, sizeof(t_convert));
	c.fp = (char *)format;
	c.buffer = ret;
	va_copy(c.args, args);
	printf_core(&c);
	va_end(c.args);
	return (c.ret_len);
}
