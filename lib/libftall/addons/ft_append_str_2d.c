/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_str_2d.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:15:01 by lmells            #+#    #+#             */
/*   Updated: 2023/08/28 22:38:40 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftall.h>

char	**ft_append_str_2d(char **array, char *str)
{
	char	**append;
	size_t	array_len;
	size_t	i;

	array_len = ft_2d_array_len(array);
	append = ft_calloc(array_len + 2, sizeof(char *));
	if (!append)
		return (array);
	append[array_len] = ft_strdup(str);
	i = 0;
	while (i < array_len)
	{
		append[i] = ft_strdup(array[i]);
		if (!append[i])
		{
			ft_free_str_2d(append, i);
			return (array);
		}
		i++;
	}
	if (array)
		ft_free_str_2d(array, array_len);
	return (append);
}
