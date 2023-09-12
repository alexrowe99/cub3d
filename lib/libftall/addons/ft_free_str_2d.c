/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_2d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 22:35:49 by lmells            #+#    #+#             */
/*   Updated: 2023/08/29 22:46:26 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftall.h>

void	ft_free_str_2d(char **array, size_t len)
{
	if (array)
	{
		if (!len)
			len = ft_2d_array_len(array);
		while (len--)
		{
			if (array[len])
				free(array[len]);
			array[len] = NULL;
		}
		free(array);
	}
	array = NULL;
}
