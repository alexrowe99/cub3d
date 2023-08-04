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

// int	player_movement_up(t_entity *player)
// {
// 	player->vertex.position.y -= 5;
// 	player->vertex.colour = 0x00FFFF;
// 	return (0);
// }

// int	player_movement_down(t_entity *player)
// {
// 	player->vertex.position.y += 5;
// 	player->vertex.colour = 0xDA552B;
// 	return (0);
// }

int	player_movement_left(t_entity *player, float dt)
{
	player->velocity += (world.gravity/player->mass) * dt;
	player->vertex.position.x -= player->velocity * dt;
	player->vertex.colour = 0x40EB34;
	return (0);
}

int	player_movement_right(t_entity *player, float dt)
{
	player->velocity += (world.gravity/player->mass) * dt;
	player->vertex.position.x += player->velocity * dt;
	player->vertex.colour = 0xEBCC34;
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
	for (size_t i = 0; i < SUPPORTED_KEYCODE_COUNT; i++)
	{
		if (keycode == bench.events.key_press[i].code)
			bench.events.key_press[i].active = false;
	}
	return (keycode);
}

void	draw_player(t_entity *player)
{
	t_vertex	v;

	v = player->vertex;
	csketch_circle(v.position.x, v.position.y, 10, v.colour);
}

void	game_loop(float dt)
{
	// if (key_is_down(KEY_W))
	// 	player_movement_up(&world.player, dt);
	// if (key_is_down(KEY_S))
	// 	player_movement_down(&world.player, dt);
	if (key_is_down(KEY_A))
		player_movement_left(&world.player, dt);
	else if (key_is_down(KEY_D))
		player_movement_right(&world.player, dt);
	else
		world.player.velocity = 100.0f;
}

// #define FPS_LIMIT 60

#include <time.h>
// double time = 0.0f;
// double delta_time = 1 / FPS_LIMIT;

clock_t	cltimer;
static int	update(void)
{
	double dt = clock() - cltimer;
	fprintf(stderr, "Time since last frame: %fseconds\n", dt/CLOCKS_PER_SEC);
	cltimer = clock();
	game_loop(dt/CLOCKS_PER_SEC);

	csketch_clear();
	draw_player(&world.player);

	mlx_put_image_to_window(bench.mlx.mlx_ptr, bench.mlx.win_ptr, final_csketch(), 0, 0);

	// t = clock() - t;
	// double elapsed_ms = (((double)t)/CLOCKS_PER_SEC*1000);
	// fprintf(stdout, "Elapsed Time: %.3fms | FPS: %d\n", elapsed_ms, (int)(1000/elapsed_ms));
	
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

	world.gravity = 600.0f;

	t_entity	*player = &world.player;

	player->velocity = 100.0f;
	player->mass = 5.0f;
	player->vertex.colour = 0xFFFFFF;
	player->vertex.position.x = WIN_WIDTH/2;
	player->vertex.position.y = WIN_HEIGHT/2;

	cltimer = clock();
	mlx_loop_hook(mlx->mlx_ptr, update, NULL);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
