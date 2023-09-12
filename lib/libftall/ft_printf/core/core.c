/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:34:40 by lmells            #+#    #+#             */
/*   Updated: 2023/08/25 10:29:41 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_core.h>

static char	*convert_args(char *fp, t_convert *c)
{
	c->ok = 0;
	if (*fp == '%')
		c->ok = convert_char('%', c);
	else if (*fp == 'c')
		c->ok = convert_char(va_arg(c->args, int), c);
	else if (*fp == 's')
		c->ok = convert_str(va_arg(c->args, char *), c);
	else if (*fp == 'd' || *fp == 'i')
		c->ok = convert_dec(1, va_arg(c->args, int), c);
	else if (*fp == 'u')
		c->ok = convert_dec(0, va_arg(c->args, unsigned int), c);
	else if (*fp == 'x' || *fp == 'X')
		c->ok = convert_hex(va_arg(c->args, unsigned int), *fp - ('x' - 'a'),
				c);
	else if (*fp == 'p')
	{
		c->flag.pad_len = 0;
		c->ok = convert_str("0x", c);
		c->ok = c->ok > 0 && convert_hex((uint64_t)va_arg(c->args, void *),
				'a', c);
	}
	if (!c->ok)
		return (NULL);
	return (fp + 1);
}

void	printf_core(t_convert *c)
{
	while (c->fp[0] != '\0' && c->ret_len != -1)
	{
		if (c->fp[0] == '%')
			c->fp = convert_args(get_flag_info(++c->fp, &c->flag), c);
		else
			convert_char(*c->fp++, c);
		if (!c->fp)
			break ;
	}
}
