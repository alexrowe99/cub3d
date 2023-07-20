/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:20:00 by lmells            #+#    #+#             */
/*   Updated: 2023/07/19 19:06:58 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_mlx_window(t_cub3d *app)
{
	if (DEBUG)
		printf("Exiting cub3D!\n");
	if (app->map_data)
	{
		free(app->map_data);
		app->map_data = NULL;
	}
	mlx_destroy_window(app->mlx.data, app->mlx.window);
	exit(1);
	return (0);
}

int	key_press(int keycode, t_cub3d *app)
{
	if (DEBUG)
		printf("Key Pressed: %i...\t", keycode);
	if (MACOS)
	{
		if (keycode == KEY_ESC)
			return (close_mlx_window(app));
		printf("NOT YET IMPLEMENTED!\n");
	}
	return (keycode);
}
