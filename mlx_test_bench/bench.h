#ifndef BENCH_H
# define BENCH_H

# include <stdio.h>

# ifndef WIN_WIDTH
#  define WIN_WIDTH 1280
# endif
# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 720
# endif
# ifndef WIN_TITLE
#  define WIN_TITLE "MLX Test Bench"
# endif

enum e_supported_key_code_index
{
	I_ESC,
	I_W,
	SUPPORTED_KEYCODE_COUNT
};

enum e_supported_key_codes_MACOS
{
	KEY_ESC = 53,
	KEY_W = 13
};

typedef struct s_key_event
{
	unsigned char	code;
	void			(*handler)();
}	t_key_event;

typedef struct s_events
{
	t_key_event	key_press[SUPPORTED_KEYCODE_COUNT];
}	t_event;

typedef struct s_mlx_structure
{
	void		*mlx_ptr;
	void		*win_ptr;
}	t_mlx;

typedef struct s_test_bench
{
	t_mlx		mlx;
	t_event		events;
}	t_bench;

#endif