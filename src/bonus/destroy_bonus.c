/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:54:58 by lmells            #+#    #+#             */
/*   Updated: 2023/12/06 09:39:54 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bonus/cub3d_bonus.h>

// Dont need to destroy map or player sprite as they are in the layer's
// image list and will be destroyed with the parent layer.
void	destroy_world(t_world **world)
{
	t_map	*map;

	map = &(*world)->map;
	while (map->size.height--)
	{
		free(map->tiles[map->size.height]);
		map->tiles[map->size.height] = (void *)0;
	}
	free(map->tiles);
	free(*world);
	*world = (void *)0;
}

int	destroy_cub3d(t_cub3d *app)
{
	int		i;

	i = TEXTURE_COUNT;
	while (i--)
	{
		if (app->wall_texture_paths[i])
		{
			free(app->wall_texture_paths[i]);
			app->wall_texture_paths[i] = (void *)0;
		}
	}
	destroy_world(&app->world);
	return (1);
}
