/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:23:01 by lmells            #+#    #+#             */
/*   Updated: 2023/10/11 09:36:14 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftall.h>

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
	size_t			n_info[2];
	char			*s;
	unsigned int	un;
	long			ln;

	ln = n;
	if (ln < INT32_MIN || ln > INT32_MAX)
		return (NULL);
	n_info[0] = 0;
	un = convert_to_unsigned(n, &n_info[0]);
	n_info[1] = get_uint_len(un);
	s = malloc(n_info[1] + n_info[0] + 1);
	if (!s)
		return (NULL);
	s[n_info[0] + n_info[1]] = '\0';
	while (n_info[1]--)
	{
		s[n_info[0] + n_info[1]] = un % 10 + '0';
		un /= 10;
	}
	if (n_info[0])
		s[0] = '-';
	return (s);
}
