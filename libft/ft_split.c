/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arowe <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:58:45 by arowe             #+#    #+#             */
/*   Updated: 2021/10/08 12:58:45 by arowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_fillsplit(const char *str, char c, char **split, int len)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (i < len)
	{
		j = 0;
		while (str[i + j] != c && str[i + j])
			j++;
		if (j != 0)
		{
			split[k] = (char *)malloc(sizeof(char) * (j + 1));
			if (!split[k])
				return (-1);
			ft_strlcpy(split[k], &str[i], j + 1);
			k++;
		}
		i++;
		i += j;
	}
	return (k);
}

char	**ft_split(const char *s, char c)
{
	char	**split;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] == c)
			k++;
		i++;
	}
	split = (char **)malloc(sizeof(char *) * (k + 2));
	if (!split)
		return (NULL);
	k = ft_fillsplit(s, c, split, i);
	if (k == -1)
		return (NULL);
	split[k] = NULL;
	return (split);
}
