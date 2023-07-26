/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:25:16 by lmells            #+#    #+#             */
/*   Updated: 2023/07/26 09:39:58 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_free(t_map **data)
{
	if (*data)
	{
		if ((*data)->tiles)
		{
			while ((*data)->map_height--)
			{
				if ((*data)->tiles[(*data)->map_height])
					free((*data)->tiles[(*data)->map_height]);
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
	ft_bzero(&app, sizeof(t_cub3d));
	initialise_cub3d(&app, v[--c]);
	mlx_loop(app.mlx.data);
	return (0);
}
