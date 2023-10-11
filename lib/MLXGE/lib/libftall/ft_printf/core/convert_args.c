/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 09:52:47 by lmells            #+#    #+#             */
/*   Updated: 2023/08/25 10:16:40 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_core.h>

int	convert_char(int ch, t_convert *c)
{
	if ((!c->ret_len && !init_buffer(c))
		|| (c->ret_len == c->bs && resize_buffer(c) == -1))
		return (conversion_failure(c));
	(*c->buffer)[c->ret_len++] = ch;
	(*c->buffer)[c->ret_len] = '\0';
	return (c->ret_len);
}

int	convert_str(const char *s, t_convert *c)
{
	size_t	s_len;

	if (!c->ret_len && !init_buffer(c))
		return (conversion_failure(c));
	s_len = ft_strlen(s);
	while ((int)(c->ret_len + s_len) >= c->bs)
	{
		if (resize_buffer(c) == -1)
			return (conversion_failure(c));
	}
	ft_memcpy(&(*c->buffer)[c->ret_len], s, s_len);
	c->ret_len += s_len;
	(*c->buffer)[c->ret_len] = '\0';
	return (c->ret_len);
}

int	convert_dec(uint8_t sign, uint64_t n, t_convert *c)
{
	int64_t	sn;
	char	*output;

	if (sign)
	{
		sn = (int64_t)n;
		if (sn < 0)
		{
			if (convert_char('-', c) == -1)
				return (conversion_failure(c));
			sn = -sn;
			if (c->flag.pad_len)
				c->flag.pad_len--;
		}
		n = sn;
	}
	output = outfmt_decimal(n, get_unsigned_len_base(n, 10), c);
	if (!output)
		return (conversion_failure(c));
	convert_str(output, c);
	free(output);
	if (c->ret_len == -1)
		return (conversion_failure(c));
	return (c->ret_len);
}

int	convert_hex(uint64_t n, int alpha, t_convert *c)
{
	char	*output;

	output = outfmt_hexadecimal(n, get_unsigned_len_base(n, 16), alpha, c);
	if (!output)
		return (conversion_failure(c));
	convert_str(output, c);
	free(output);
	if (c->ret_len == -1)
		return (conversion_failure(c));
	return (c->ret_len);
}
