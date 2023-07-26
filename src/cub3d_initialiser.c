/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_initialiser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:54:13 by lmells            #+#    #+#             */
/*   Updated: 2023/07/25 12:29:32 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_file_extension(const char *map_filepath)
{
	char	*extension;
	char	*error_message;

	error_message = NULL;
	extension = ft_strrchr(map_filepath, '.');
	if (!extension || ft_strncmp(".cub", extension, ft_strlen(".cub")))
	{
		error_message = ft_strjoin(map_filepath, " is not a .cub map file.");
		print_error(error_message);
		free(error_message);
		exit(1);
	}
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
	t_initialiser	init;

	validate_file_extension(map_filepath);

	ft_bzero(&init, sizeof(t_initialiser));
	if (*initialise_map_data(map_filepath, &app->map_data, &init)->error)
		validation_exit(&init.validation, &app->map_data);
	free_validator(&init.validation);
	
	
	if (!initialise_mlx(&app->mlx, app))
		exit_free(&app->map_data);
	
	if (DEBUG)
		printf("CUB3D INTIALISED SUCCESSFULLY!\n");
}
