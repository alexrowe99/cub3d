#include <stdio.h>
#include <stdlib.h>

#include "../inc/macos_keycodes.h"
#include "chong_sketch.h"

#include <time.h>
#include <unistd.h>

# define WIDTH 1280
# define HEIGHT 720

typedef	struct s_bench
{
	void	*mlx;
	void	*window;
}	t_bench;

int	key_press(int keycode, t_bench *bench)
{
	if (keycode == KEY_ESC)
	{
		csketch_gc();
		mlx_destroy_window(bench->mlx, bench->window);
		exit(0);
	}
	return (keycode);
}

# define GRID_W 10
# define GRID_H 7

typedef struct s_vec_2_int
{
	int	x;
	int	y;
}	t_v2i;

typedef struct s_vertex
{
	t_v2i		position;
	uint32_t	colour;
}	t_vertex;

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	main(void)
{
	t_bench	bench;

	bench.mlx = mlx_init();
	if (!bench.mlx)
	{
		fprintf(stderr, "Error: Could not initialise mlx pointer.\n");
		return (1);
	}
	bench.window = mlx_new_window(bench.mlx, WIDTH, HEIGHT, "Chong Sketch: Test Bench");
	if (!bench.window)
	{
		fprintf(stderr, "Error: Could not initialise mlx pointer.\n");
		return (1);
	}
	// mlx_key_hook(bench.window, key_press, &bench);

	t_csketch_errno err = csketch_init(bench.mlx, bench.window, WIDTH, HEIGHT);
	if (err)
	{
		fprintf(stderr, "Error: Could not initialise chong sketch canvas: %s\n", csketch_errno(err));
		return (err);
	}

	// csketch_fill(WIDTH, HEIGHT, 0x2B2B2B);
	// csketch_rectangle(600, 400, WIDTH/2 - 600/2, HEIGHT/2 - 400/2, 0xFFFFFF);
	// csketch_circle(WIDTH/2, HEIGHT/2, 120, 0xFF0000);
	
	// csketch_line(100, 100, 700, 500, 0x20FF20);	// Works...
	// csketch_line(700-1, 100, 100-1, 500, 0x20FF20);	// Works...
	// csketch_line(WIDTH/2, 100, WIDTH/2, 500, 0x20FF20);	// Works...
	// csketch_line(100, HEIGHT/2, 700, HEIGHT/2, 0x20FF20);	// Works...

	char	grid[GRID_H][GRID_W] = {
		{'1','1','1','1','1','1','1','1','1','1'},
		{'1','0','0','0','0','1','0','0','0','1'},
		{'1','0','0','1','0','0','0','0','0','1'},
		{'1','0','0','1','0','0','0','0','0','1'},
		{'1','0','0','0','0','1','0','0','0','1'},
		{'1','0','0','0','0','1','0','0','0','1'},
		{'1','1','1','1','1','1','1','1','1','1'},
	};

	size_t tile_size = 64;
	t_vertex vertices[GRID_W * GRID_H];

	for (size_t	y = 0; y < GRID_H; y++)
	{
		for (size_t x = 0; x < GRID_W; x++)
		{
			t_vertex *v = &vertices[y * GRID_W + x];
			v->position.x = x * tile_size;
			v->position.y = y * tile_size;
			if (grid[y][x] == '1')
				v->colour = 0x4848A8;
			else
				v->colour = 0xBFBFBF;
		}
	}

	// Render Loop.
	const char *htag = "Rendering...\t";
	write(STDOUT_FILENO, htag, ft_strlen(htag));
	clock_t time = clock();

	csketch_clear();
	csketch_fill(WIDTH, HEIGHT, 0x2B2B2B);
	for (size_t y = 0; y < GRID_H; y++)
	{
		for (size_t x = 0; x < GRID_W; x++)
		{
			t_vertex v = vertices[y * GRID_W + x];
			t_v2i p = v.position;
			p.x += WIDTH/2 - (GRID_W*tile_size)/2;
			p.y += HEIGHT/2 - (GRID_H*tile_size)/2;
			csketch_rectangle(tile_size, tile_size, p.x, p.y, v.colour);
			csketch_line(p.x, p.y, p.x + tile_size, p.y, 0);
			csketch_line(p.x, p.y, p.x, p.y + tile_size, 0);
			if (y == GRID_H - 1)
				csketch_line(p.x, p.y + tile_size, p.x + tile_size, p.y + tile_size, 0);
			if (x == GRID_W - 1)
				csketch_line(p.x + tile_size, p.y, p.x + tile_size, p.y + tile_size, 0);
		}
	}

	time = clock() - time;
	double elapsed = (((double)time)/CLOCKS_PER_SEC)*1000;
	fprintf(stdout, "Elapsed Time: %.3fms\n", elapsed);
	fprintf(stdout, "FPS: %d\n", (int)(1000/elapsed));

	err = csketch_outppm("grid.ppm", WIDTH, HEIGHT);
	if (err)
	{
		fprintf(stderr, "Error: Could not write to ppm file \"grid.ppm\": %s\n", csketch_errno(err));
		return (err);
	}
	mlx_destroy_image(bench.mlx, final_csketch());
	csketch_gc();
	// mlx_put_image_to_window(bench.mlx, bench.window, final_csketch(), 0, 0);
	// mlx_loop(bench.mlx);
	return (0);
}
