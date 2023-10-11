/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:02:54 by lmells            #+#    #+#             */
/*   Updated: 2023/09/05 18:40:04 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftall.h>

char	**ft_strdup_2d(char **array)
{
	size_t	i;
	size_t	array_len;
	char	**dup;

	array_len = ft_2d_array_len(array);
	if (!array_len)
		return (NULL);
	dup = ft_calloc(array_len + 1, sizeof(char *));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < array_len)
	{
		dup[i] = ft_strdup(array[i]);
		if (!dup[i])
		{
			ft_free_str_2d(dup, i);
			dup = NULL;
			return (NULL);
		}
		i++;
	}
	return (dup);
}
