#include "cub3d.h"

#define TEXT_RED "\e[0;91m"
#define TEXT_WHITE "\e[0m"

int	close_mlx_window(t_mlx_data *mlx)
{
	mlx_destroy_window(mlx->data, mlx->window);
	exit(1);
	return (0);
}

int	key_press(int keycode, t_mlx_data *mlx)
{
	if (MACOS)
	{
		if (keycode == KEY_ESC)
			return (close_mlx_window(mlx));
		printf("NOT YET IMPLEMENTED!\n");
	}
	return (keycode);
}

static bool	validate_args(int c, char **v)
{
	char	*file_extension;

	if (c != 2)
	{
		write(STDERR_FILENO, TEXT_RED "Error", ft_strlen(TEXT_RED "Error"));
		write(STDERR_FILENO, TEXT_WHITE " : Incorrect number of arguments.\n",
			ft_strlen(TEXT_WHITE " : Incorrect number of arguments.\n"));
		return (false);
	}
	file_extension = ft_strrchr(v[1], '.');
	if (!file_extension
		|| ft_strncmp(".cub", file_extension, ft_strlen(".cub")))
	{
		write(STDERR_FILENO, TEXT_RED "Error", ft_strlen(TEXT_RED "Error"));
		write(STDERR_FILENO, TEXT_WHITE " : \"", ft_strlen(TEXT_WHITE " : \""));
		write(STDERR_FILENO, v[1], ft_strlen(v[1]));
		write(STDERR_FILENO, "\" is not a '.cub' map file.\n",
			ft_strlen("\" is not a '.cub' map file.\n"));
		return (false);
	}
	return (true);
}

void	initialise_mlx(t_mlx_data *mlx)
{
	mlx->data = mlx_init();
	mlx->window = mlx_new_window(mlx->data, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!mlx->window)
	{
		fprintf(stderr, "\e[0;91mError\e[0m : Failed to create a new window.\n");
		exit(1);
	}
	mlx_key_hook(mlx->window, key_press, mlx);
	mlx_hook(mlx->window, 17, 0, close_mlx_window, mlx);
}

int	main(int c, char **v)
{
	t_cub3d	app;

	if (!validate_args(c, v))
		return (1);
	initialise_mlx(&app.mlx);
	mlx_loop(app.mlx.data);
	return (0);
}
