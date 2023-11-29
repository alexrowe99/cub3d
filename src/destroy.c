/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:54:58 by lmells            #+#    #+#             */
/*   Updated: 2023/11/28 21:44:33 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// Dont need to destroy map or player sprite as they are in the layer's
// image list and will be destroyed with the parent layer.
static void	destroy_world(t_world *world)
{
	while (world->map.size.height--)
	{
		free(world->map.tiles[world->map.size.height]);
		world->map.tiles[world->map.size.height] = (void *)0;
	}
	free(world->map.tiles);
}

int	destroy_cub3d(t_cub3d *app)
{
	int	i;

	destroy_world(&app->world);
	i = TEXTURE_COUNT;
	while (i--)
	{
		if (app->wall_texture_paths[i])
		{
			free(app->wall_texture_paths[i]);
			app->wall_texture_paths[i] = (void *)0;
		}
	}
	return (1);
}
