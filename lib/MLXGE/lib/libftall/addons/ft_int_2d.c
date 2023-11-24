/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:32:21 by lmells            #+#    #+#             */
/*   Updated: 2023/11/09 12:49:01 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftall.h>

void	*ft_free_2d_int_n(int **array, size_t n)
{
	while (n--)
		free(array[n]);
	free(array);
	return ((void *)0);
}

static inline size_t	int_array_len(int *array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	**ft_dup_2d_int_n(int **array, size_t n)
{
	size_t	len;
	size_t	i;
	int		**dup;

	dup = ft_calloc(n + 1, sizeof(int *));
	if (!dup)
		return ((void *)0);
	i = 0;
	while (i < n)
	{
		len = int_array_len(array[i]);
		dup[i] = ft_calloc(len + 1, sizeof(int));
		if (!dup[i] || !ft_memcpy(dup[i], array[i], len * sizeof(int)))
			return (ft_free_2d_int_n(dup, n));
		i++;
	}
	return (dup);
}
