/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:32:13 by lmells            #+#    #+#             */
/*   Updated: 2023/07/10 15:32:50 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	in_charset(int c, int set_c, size_t *pos_index, int direction)
{
	if (c == set_c)
	{
		*pos_index += direction;
		return (1);
	}
	return (0);
}

static size_t	start_position(const char *s1, const char *set, size_t set_len)
{
	size_t	i;
	size_t	pos;

	pos = 0;
	while (s1[pos] != '\0')
	{
		i = 0;
		while (set[i] != '\0')
		{
			if (in_charset(s1[pos], set[i], &pos, 1))
				break ;
			i++;
		}
		if (i == set_len)
			break ;
	}
	return (pos);
}

static size_t	end_position(const char *s1, const char *set, size_t set_len)
{
	size_t	i;
	size_t	pos;

	pos = ft_strlen(s1);
	while (pos)
	{
		i = 0;
		while (set[i] != '\0')
		{
			if (in_charset(s1[pos - 1], set[i], &pos, -1))
				break ;
			i++;
		}
		if (i == set_len)
			break ;
	}
	return (pos);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t		set_len;
	size_t		start;
	size_t		end;

	set_len = ft_strlen(set);
	start = start_position(s1, set, set_len);
	end = end_position(s1, set, set_len);
	return (ft_substr(s1, start, end - start));
}
