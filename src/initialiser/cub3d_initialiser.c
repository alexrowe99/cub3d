/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_initialiser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:54:13 by lmells            #+#    #+#             */
/*   Updated: 2023/07/20 11:40:44 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	validate_file_extension(const char *map_filepath)
{
	char	*file_extension;
	char	*error_message;

	error_message = NULL;
	file_extension = ft_strrchr(map_filepath, '.');
	if (!file_extension
		|| ft_strncmp(".cub", file_extension, ft_strlen(".cub")))
	{
		error_message = ft_strjoin(map_filepath, " is not a .cub map file.");
		print_error(error_message);
		free(error_message);
		return (false);
	}
	return (true);
}

bool	initialise_mlx(t_mlx *mlx, t_cub3d *app)
{
	mlx->data = mlx_init();
	mlx->window = mlx_new_window(mlx->data, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!mlx->window)
		return (print_error("Failed to create a new window."));
	mlx_hook(mlx->window, 17, 0, close_mlx_window, app);
	mlx_key_hook(mlx->window, key_press, app);
	return (true);
}

void	initialise_cub3d(t_cub3d *app, const char *map_filepath)
{
	ft_bzero(app, sizeof(t_cub3d));
	if (!validate_file_extension(map_filepath)
		|| !initialise_map_data(map_filepath, &app->map_data))
		exit_free(&app->map_data);

	// Initialise mlx here...
	if (!initialise_mlx(&app->mlx, app))
		exit_free(&app->map_data);

	if (DEBUG)
		printf("CUB3D INTIALISED SUCCESSFULLY!\n");
}
