#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "get_next_line.h"
# include "libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

#ifndef MACOS
# define MACOS 1
# include "macos_keycodes.h"
#endif

#ifndef WIN_TITLE
# define WIN_TITLE "cub3D - Alex & Leighton"
#endif
#ifndef WIN_WIDTH
# define WIN_WIDTH 1280
#endif
#ifndef WIN_HEIGHT
# define WIN_HEIGHT 720
#endif

typedef struct s_mlx_data
{
	void	*data;
	void	*window;
}	t_mlx_data;

typedef struct s_cub3d
{
	t_mlx_data	mlx;
}	t_cub3d;

#endif
