#include <mlxge.h>

#define WIN_W 800
#define WIN_H 600

typedef struct s_vector_2_double
{
	double	x;
	double	y;
}	t_v2d;

t_v2d	v2d(double x, double y)
{
	return ((t_v2d){.x=x, .y=y});
}

t_v2d	v2d_sum(t_v2d a, t_v2d b)
{
	return ((t_v2d){.x=a.x+b.x, .y=a.y+b.y});
}

typedef struct s_player
{
	bool	has_moved;
	t_v2d	move;
	double	movement_speed;
	t_v2d	position;
}	t_player;

typedef struct s_game
{
	t_player	player;
	t_layer		*render;
}	t_game;

enum s_key_events
{
	W, S, A, D,
	COUNT_KEYS
};

struct s_key_input
{
	int		code;
	bool	is_down;
};

static struct s_key_input	handle_key[COUNT_KEYS];

static int	load_input(void *handle_index)
{
	// ft_printf("%s: Loading input [%i]\n", __func__, *(int *)handle_index);
	handle_key[*(int *)handle_index].is_down = true;
	return (0);
}

static int	remove_input(void *handle_index)
{
	// ft_printf("%s: Removing input [%i]\n", __func__, *(int *)handle_index);
	handle_key[*(int *)handle_index].is_down = false;
	return (0);
}

static bool	key_is_down(int handle_index)
{
	return (handle_key[handle_index].is_down);
}

struct game_key_events
{
	int		index;
	int		type;
	int		code;
};

static struct game_key_events	handle_input[COUNT_KEYS] = {
	{.index = 0, .type = PRESSED, .code = KEY_W},
	{.index = 0, .type = PRESSED, .code = KEY_S},
	{.index = 0, .type = PRESSED, .code = KEY_A},
	{.index = 0, .type = PRESSED, .code = KEY_D},
};

static t_game	*game(void)
{
	static t_game	game;

	return (&game);
}

static void	draw_scene(void *frame, t_player player)
{
	mlxge_fill_frame(frame, 0x4a4a4a);
	mlxge_draw_circle(frame, player.position.x, player.position.y, 20, 0x3dab9c);
}

static void	load_scene()
{
	game()->player.movement_speed = 5.0f;
	game()->player.position = v2d(WIN_W/2, WIN_H/2);
	draw_scene(game()->render->frame, game()->player);
}

static int	game_loop(t_layer *game_layer)
{
	t_player	*player;

	player = &game()->player;

	if (key_is_down(W))
	{
		player->position.y -= player->movement_speed;
	}
	if (key_is_down(S))
	{
		player->position.y += player->movement_speed;
	}
	if (key_is_down(A))
	{
		player->position.x -= player->movement_speed;
	}
	if (key_is_down(D))
	{
		player->position.x += player->movement_speed;
	}

	draw_scene(game_layer->frame, game()->player);
	return (0);
}

int	main(void)
{
	mlxge_init();
	if (mlxge_create_window(WIN_W, WIN_H, "Test Window - WSL") < 0)
		return (-1);

	game()->render = mlxge_new_layer(WIN_W, WIN_H, game_loop);
	if (!game()->render)
		exit(mlxge_destroy());
	
	load_scene();

	// Pressed Events
	for (int i = 0; i < COUNT_KEYS; i++)
	{
		struct game_key_events	*input = &handle_input[i];
		input->index = i;
		void	*event = mlxge_new_key_event(input->type, input->code, load_input, &input->index);
		if (!event)
			exit(mlxge_destroy());
		mlxge_push_event(event, game()->render->event_list);
	}
	// Released Events
	for (int i = 0; i < COUNT_KEYS; i++)
	{
		struct game_key_events	*input = &handle_input[i];
		void	*event = mlxge_new_key_event(RELEASED, input->code, remove_input, &input->index);
		if (!event)
			exit(mlxge_destroy());
		mlxge_push_event(event, game()->render->event_list);
	}

	mlxge_push_layer(game()->render);

	return (mlxge_run());
}
