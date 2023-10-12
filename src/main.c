/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:10:53 by lmells            #+#    #+#             */
/*   Updated: 2023/10/12 10:10:37 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	cub3d_error(const char *format_message, ...)
{
	char	*output;
	va_list	argp;

	ft_printf("\e[0;91mError\e[0m\n");
	va_start(argp, format_message);
	ft_vasprintf(&output, format_message, argp);
	va_end(argp);
	if (errno)
		perror(output);
	else
		ft_printf("%s\n", output);
	free(output);
	return (true);
}

int	destroy_cub3d(void *app_ptr)
{
	size_t	i;
	t_cub3d	*app;

	app = (t_cub3d *)app_ptr;
	i = TEXTURE_COUNT;
	while (i--)
	{
		ft_vfree(1, &app->texture_paths[i]);
		if (i < RGB_COUNT)
			ft_vfree(1, &app->rgb_floor_ceiling[i]);
	}
	if (app->map_tiles)
	{
		while (app->m_dim.y)
			ft_vfree(1, &app->map_tiles[--app->m_dim.y]);
		free(app->map_tiles);
	}
	app->map_tiles = NULL;
	return (0);
}

static bool	validate_args(int ac, char **av)
{
	char	*ext;

	if (ac != 2)
		return (!cub3d_error("Incorrect number of arguments"));
	ext = ft_strrchr(av[1], '.');
	if (!ext || ft_strncmp(".cub", ext, 4))
		return (!cub3d_error("Argument \"%s\" is not a .cub map file", av[1]));
	return (true);
}

// struct s_mlx {
// 	void	*inst;
// 	void	*win;
// };

// int	close_window(struct s_mlx *app)
// {
// 	printf("On Destroy Event Triggered! Closing application window...");
// 	exit(mlx_destroy_window(app->inst, app->win));
// 	return (0);
// }

// int	key_press_event = 0;

// int	handle_key_press(int keycode, void *param)
// {
// 	(void)param;
// 	printf("Key Press Event Triggered! Keycode = %i;\n", keycode);
// 	key_press_event++;
// 	return (keycode);
// }

int	update_cub3d(void *param)
{
	(void)param;
	printf("Updating Cub3d...\n");
	return (0);
}

int	main(int ac, char **av)
{
	// struct s_mlx	app;

	// app.inst = mlx_init();
	// if (!app.inst || !validate_args(ac, av))
	// 	return (1);
	// app.win = mlx_new_window(app.inst, 800, 600, "test events");
	// mlx_hook(app.win, 17, 0, close_window, &app);
	
	// mlx_do_key_autorepeatoff(app.inst);
	// mlx_hook(app.win, 2, 0, handle_key_press, NULL);
	
	// mlx_loop_hook(app.inst, update_cub3d, NULL);
	// return (mlx_loop(app.inst));

	// t_cub3d	app;

	// if (!validate_args(ac, av) || engine_init(WIN_W, WIN_H, TITLE) < 0)
	// 	return (engine_destroy());
	// engine_bind_application(&app, destroy_cub3d, update_cub3d);

	// ft_bzero(&app, sizeof(t_cub3d));
	// if (!parse_map_file(&app, av[1]))
	// 	return (engine_destroy());

	// return (engine_start_application());

	if (!validate_args(ac, av))
		return (-1);

	mlxge_init();
	if (mlxge_create_window(WIN_W, WIN_H, TITLE) < 0)
		return (mlxge_destroy());
	t_layer	*render_game = mlxge_new_layer(WIN_W, WIN_H, update_cub3d);
	if (!render_game)
		return (mlxge_destroy());
	mlxge_fill_frame(render_game->frame, 0xC84B3F);
	mlxge_push_layer(render_game);
	return (mlxge_run());
}
