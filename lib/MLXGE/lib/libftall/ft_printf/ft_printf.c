/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:16:41 by lmells            #+#    #+#             */
/*   Updated: 2023/08/24 11:24:31 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_core.h>

void	putstr(const char *s, t_convert *c)
{
	while (*s != '\0')
		c->ret_len += write(1, s++, 1);
}

void	putdec(uint8_t sign, uint64_t n, t_convert *c)
{
	int64_t	sn;
	char	*output;

	if (sign)
	{
		sn = (int64_t)n;
		if (sn < 0)
		{
			c->ret_len += write(1, "-", 1);
			sn = -sn;
			if (c->flag.pad_len)
				c->flag.pad_len--;
		}
		n = sn;
	}
	output = outfmt_decimal(n, get_unsigned_len_base(n, 10), c);
	if (!output)
	{
		c->ret_len = -1;
		return ;
	}
	putstr(output, c);
	free(output);
}

void	puthex(uint64_t n, int alpha, t_convert *c)
{
	char	*output;

	output = outfmt_hexadecimal(n, get_unsigned_len_base(n, 16), alpha, c);
	if (!output)
	{
		c->ret_len = -1;
		return ;
	}
	putstr(output, c);
	free(output);
}

static char	*conversion(char *fp, t_convert *c)
{
	int	ch;

	ch = '%';
	if (*fp == '%' || *fp == 'c')
	{
		if (*fp == 'c')
			ch = va_arg(c->args, int);
		c->ret_len += write(1, &ch, 1);
	}
	else if (*fp == 's')
		putstr(va_arg(c->args, char *), c);
	else if (*fp == 'i' || *fp == 'd')
		putdec(1, va_arg(c->args, int), c);
	else if (*fp == 'u')
		putdec(0, va_arg(c->args, unsigned int), c);
	else if (*fp == 'x' || *fp == 'X')
		puthex(va_arg(c->args, unsigned int), *fp - ('x' - 'a'), c);
	else if (*fp == 'p')
	{
		c->flag.pad_len = 0;
		putstr("0x", c);
		puthex((uint64_t)va_arg(c->args, void *), 'a', c);
	}
	return (fp + 1);
}

int	ft_printf(const char *fmt, ...)
{
	t_convert	c;

	ft_bzero(&c, sizeof(t_convert));
	c.fp = (char *)fmt;
	va_start(c.args, fmt);
	while (c.fp[0] != '\0' && c.ret_len != -1)
	{
		if (c.fp[0] == '%')
			c.fp = conversion(get_flag_info(++c.fp, &c.flag), &c);
		else
			c.ret_len += write(1, c.fp++, 1);
	}
	va_end(c.args);
	return (c.ret_len);
}
