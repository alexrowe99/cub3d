/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:23:01 by lmells            #+#    #+#             */
/*   Updated: 2023/07/12 15:01:44 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	get_uint_len(unsigned int n)
{
	size_t	len;

	len = 0;
	if (!n)
		return (1);
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static unsigned int	convert_to_unsigned(int n, size_t *sign)
{
	if (n < 0)
	{
		n *= -1;
		*sign = 1;
	}
	return (n);
}

char	*ft_itoa(int n)
{
	size_t			n_len;
	size_t			sign;
	char			*s;
	unsigned int	un;

	if ((long int)n < (long int)INT32_MIN - 1 || (long int)n > INT32_MAX)
		return (NULL);
	sign = 0;
	un = convert_to_unsigned(n, &sign);
	n_len = get_uint_len(un);
	s = malloc(n_len + sign + 1);
	if (!s)
		return (NULL);
	s[sign + n_len] = '\0';
	while (n_len--)
	{
		s[sign + n_len] = un % 10 + '0';
		un /= 10;
	}
	if (sign)
		s[0] = '-';
	return (s);
}
