/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resize_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 17:56:36 by lmells            #+#    #+#             */
/*   Updated: 2023/08/15 12:12:27 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftall.h>

int	ft_resize_str(char **s, size_t n)
{
	size_t	s_len;
	char	*tmp;

	s_len = ft_strlen(*s);
	tmp = malloc(s_len + n + 1);
	if (!tmp)
		return (-1);
	if (*s)
	{
		tmp = (char *)ft_memcpy(tmp, *s, s_len);
		free(*s);
	}
	s_len += n;
	tmp[s_len] = '\0';
	*s = tmp;
	return (s_len);
}
