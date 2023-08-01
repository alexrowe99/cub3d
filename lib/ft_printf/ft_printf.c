/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:16:41 by lmells            #+#    #+#             */
/*   Updated: 2023/07/23 13:40:35 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putstr(char *s)
{
	int	bytes;

	if (!s)
		return (write(1, "(null)", 6));
	bytes = 0;
	while (*s != '\0')
		bytes += write(1, s++, 1);
	return (bytes);
}

static int	putnbr_base(u_int64_t value, u_int8_t base, char alpha,
	u_int8_t init)
{
	char	*prefix;
	int		bytes;
	int		c;

	bytes = 0;
	if (alpha && init)
	{
		prefix = "0x";
		if (alpha == 'A')
			prefix = "0X";
		bytes += write(1, prefix, 2);
	}
	if (value > base - 1)
	{
		bytes += putnbr_base(value / base, base, alpha, 0);
		bytes += putnbr_base(value % base, base, alpha, 0);
	}
	else
	{
		c = value + '0';
		if (value > 9)
			c = value - 10 + alpha;
		bytes += write(1, &c, 1);
	}
	return (bytes);
}

static int	print_number(int64_t n)
{
	u_int64_t	un;
	int			bytes;

	bytes = 0;
	if (n < 0)
	{
		bytes = write(1, "-", 1);
		if (bytes == -1)
			return (-1);
		n = -n;
	}
	un = n;
	return (bytes + putnbr_base(un, 10, 0, 0));
}

static int	conversion(const char *format, va_list *ap)
{
	int	c;

	c = '%';
	if (*format == 'c' || *format == '%')
	{
		if (*format == 'c')
			c = va_arg(*ap, int);
		return (write(1, &c, 1));
	}
	else if (*format == 's')
		return (ft_putstr(va_arg(*ap, char *)));
	else if (*format == 'p')
		return (putnbr_base((u_int64_t)va_arg(*ap, void *), 16, 'a', 1));
	else if (*format == 'd' || *format == 'i')
		return (print_number(va_arg(*ap, int)));
	else if (*format == 'u')
		return (putnbr_base(va_arg(*ap, unsigned int), 10, 0, 0));
	else if (*format == 'X')
		return (putnbr_base(va_arg(*ap, unsigned int), 16, 'A', 0));
	else if (*format == 'x')
		return (putnbr_base(va_arg(*ap, unsigned int), 16, 'a', 0));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		bytes;
	va_list	ap;

	if (!format)
		return (0);
	bytes = 0;
	va_start(ap, format);
	while (*format != '\0')
	{
		if (*format == '%')
			bytes += conversion(++format, &ap);
		else
			bytes += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (bytes);
}
