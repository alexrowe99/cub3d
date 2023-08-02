#include "bench.h"
#include "chong_sketch.h"

t_bench	bench;

void	exit_test_bench(void *arg)
{
	(void)arg;

	mlx_destroy_window(bench.mlx.mlx_ptr, bench.mlx.win_ptr);
	printf("----------------------------------------\n");
	printf("Exiting Test Bench...\n");
	exit(0);
}

// Could be a much more efficient way to handle key press.
// Iterative approach will be fine as there is only 6 possible keystrokes that
// are valid in mandatory cub3d.
static int	handle_keypress(int keycode)
{
	t_key_event	*events;

	events = bench.events.key_press;
	for (size_t i = 0; i < SUPPORTED_KEYCODE_COUNT; i++)
	{
		if (keycode == events[i].code)
		{
			events[i].handler();
			return (0);
		}
	}
	printf("Key press %i is not supported.\n", keycode);
	return (keycode);
}

int	main(void)
{
	t_mlx	*mlx;

	mlx = &bench.mlx;
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
	{
		fprintf(stderr, "Error\nCould not initialise mlx pointer.\n");
		return (1);
	}
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!mlx->win_ptr)
	{
		fprintf(stderr, "Error\nCould not create a new mlx window instance.\n");
		return (1);
	}

	t_key_event	*keypress;
	keypress = bench.events.key_press;
	keypress[I_ESC].code = KEY_ESC;
	keypress[I_ESC].handler = exit_test_bench;

	mlx_hook(mlx->win_ptr, 2, 0, handle_keypress, NULL);

	mlx_loop(mlx->mlx_ptr);
	return (0);
}
