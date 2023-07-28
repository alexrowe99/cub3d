/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:25:16 by lmells            #+#    #+#             */
/*   Updated: 2023/07/28 00:36:27 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_free(t_map **data)
{
	size_t	i;

	if (*data)
	{
		if ((*data)->tiles)
		{
			while ((*data)->map_height--)
				if ((*data)->tiles[(*data)->map_height])
					free((*data)->tiles[(*data)->map_height]);
			free((*data)->tiles);
		}
		i = COUNT_TEXTURE_TYPES;
		while (i--)
			if ((*data)->texture_paths[i])
				free((*data)->texture_paths[i]);
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
