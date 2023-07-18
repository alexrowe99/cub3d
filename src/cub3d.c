#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct s_window_manager
{
	void	*mlx;
	void	*window;
}	t_window;

int	close_mlx_window(t_window *window)
{
	mlx_destroy_window(window->mlx, window->window);
	exit(1);
	return (0);
}

int main()
{
	t_window	window;

	window.mlx = mlx_init();
	window.window = mlx_new_window(window.mlx, 1920, 1080, "Hello world!");
	if (!window.window)
	{
		fprintf(stderr, "\e[0;91mError\e[0m : Failed to create a new window.\n");
		return (1);
	}
	mlx_hook(window.window, 17, 0, close_mlx_window, &window);
	mlx_loop(window.mlx);
	return (0);
}