#include "bench.h"
#include "chong_sketch.h"

t_bench	bench;
t_world	world;

int	exit_test_bench(void)
{
	mlx_destroy_window(bench.mlx.mlx_ptr, bench.mlx.win_ptr);
	printf("----------------------------------------\n");
	printf("Exiting Test Bench...\n");
	exit(0);
	return (0);
}

int	player_movement_up(void)
{
	world.player.position.y -= 5;
	world.player.colour = 0x00FFFF;
	return (0);
}

int	player_movement_down(void)
{
	world.player.position.y += 5;
	world.player.colour = 0xDA552B;
	return (0);
}

int	player_movement_left(void)
{
	world.player.position.x -= 5;
	world.player.colour = 0x40EB34;
	return (0);
}

int	player_movement_right(void)
{
	world.player.position.x += 5;
	world.player.colour = 0xEBCC34;
	return (0);
}

static int	key_press(int keycode)
{
	for (size_t i = 0; i < SUPPORTED_KEYCODE_COUNT; i++)
	{
		if (keycode == bench.events.key_press[i].code)
		{
			bench.events.key_press[i].active = true;
			if (bench.events.key_press[i].handler)
				bench.events.key_press[i].handler();
		}
	}
	return (keycode);
}

int	key_is_down(int keycode)
{
	for (size_t i = 0; i < SUPPORTED_KEYCODE_COUNT; i++)
	{
		if (keycode == bench.events.key_press[i].code)
			return (bench.events.key_press[i].active);
	}
	return (false);
}

static int	key_release(int keycode)
{
	world.player.colour = 0xFFFFFF;
	for (size_t i = 0; i < SUPPORTED_KEYCODE_COUNT; i++)
	{
		if (keycode == bench.events.key_press[i].code)
			bench.events.key_press[i].active = false;
	}
	return (keycode);
}

#include <time.h>

static int	update(void)
{
	clock_t	t = clock();

	if (key_is_down(KEY_W))
		player_movement_up();
	if (key_is_down(KEY_S))
		player_movement_down();
	if (key_is_down(KEY_A))
		player_movement_left();
	if (key_is_down(KEY_D))
		player_movement_right();
	csketch_circle(world.player.position.x, world.player.position.y, 5, world.player.colour);
	mlx_put_image_to_window(bench.mlx.mlx_ptr, bench.mlx.win_ptr, final_csketch(), 0, 0);
	csketch_clear();

	t = clock() - t;
	double elapsed_ms = (((double)t)/CLOCKS_PER_SEC*1000);
	fprintf(stdout, "Elapsed Time: %.3fms\n", elapsed_ms);
	
	return (0);
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

	keypress[I_W].code = KEY_W;
	keypress[I_S].code = KEY_S;
	keypress[I_A].code = KEY_A;
	keypress[I_D].code = KEY_D;

	mlx_hook(mlx->win_ptr, 2, 0, key_press, NULL);
	mlx_hook(mlx->win_ptr, 3, 0, key_release, NULL);
	mlx_hook(mlx->win_ptr, 17, 0, exit_test_bench, NULL);

	t_csketch_errno err = csketch_init(mlx->mlx_ptr, mlx->win_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (err)
	{
		fprintf(stderr, "Error\nCould not initialise csketch: %s\n", csketch_errno(err));
		return ((int)err);
	}

	world.player.position.x = 200;
	world.player.position.y = 500;
	world.player.colour = 0xFFFFFF;

	mlx_loop_hook(mlx->mlx_ptr, update, NULL);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
