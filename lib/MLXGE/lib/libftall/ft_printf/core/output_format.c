/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 11:22:10 by lmells            #+#    #+#             */
/*   Updated: 2023/08/24 10:53:12 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_core.h>

char	*outfmt_decimal(uint64_t n, size_t n_len, t_convert *c)
{
	char	*buff;
	size_t	buff_len;

	buff_len = c->flag.pad_len;
	if (n_len > c->flag.pad_len)
		buff_len = n_len;
	buff = malloc(buff_len + 1);
	if (!buff)
		return (NULL);
	ft_memset(buff, '0', buff_len);
	buff[buff_len--] = '\0';
	while (n_len--)
	{
		buff[buff_len--] = (n % 10) + '0';
		n /= 10;
	}
	return (buff);
}

char	*outfmt_hexadecimal(uint64_t n, size_t n_len, int alpha, t_convert *c)
{
	char	*buff;
	size_t	buff_len;

	buff_len = c->flag.pad_len;
	if (n_len > c->flag.pad_len)
		buff_len = n_len;
	buff = malloc(buff_len + 1);
	if (!buff)
		return (NULL);
	ft_memset(buff, '0', buff_len);
	buff[buff_len--] = '\0';
	while (n_len--)
	{
		buff[buff_len] = n % 16;
		if (buff[buff_len] > 9)
			buff[buff_len] = buff[buff_len] - 10 + alpha;
		else
			buff[buff_len] += '0';
		buff_len--;
		n /= 16;
	}
	return (buff);
}
