/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:25:16 by lmells            #+#    #+#             */
/*   Updated: 2023/07/23 16:27:35 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_free(t_map **data)
{
	if (*data)
	{
		if ((*data)->tiles)
		{
			while ((*data)->m_height--)
			{
				if ((*data)->tiles[(*data)->m_height])
					free((*data)->tiles[(*data)->m_height]);
			}
			free((*data)->tiles);
		}
		free(*data);
	}
	*data = NULL;
	exit(1);
}

int	main(int c, char **v)
{
	t_cub3d	app;

	if (c != 2)
		return ((*(int *)print_error("Incorrect number of arguments.")) + 1);
	initialise_cub3d(&app, v[--c]);
	mlx_loop(app.mlx.data);
	return (0);
}
