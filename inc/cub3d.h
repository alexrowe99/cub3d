/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:23:39 by lmells            #+#    #+#             */
/*   Updated: 2023/07/20 20:51:06 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ===========================================================
	!! Cub3D header file !!
=========================================================== */

#ifndef CUB3D_H
# define CUB3D_H

/* ===========================================================
	Includes.
=========================================================== */

# ifndef MACOS
#  define MACOS 1
# endif
# ifdef MACOS
#  include "macos_keycodes.h"
# endif

# include "mlx.h"
# include "get_next_line.h"
# include "libft.h"

# include "cub3D_error.h"

# include <stdio.h>
# include <stdbool.h>
# include <stdarg.h>

/* ===========================================================
	Debug definition to avoid inellisense errors.
=========================================================== */

# ifndef DEBUG
#  define DEBUG 0
# endif

/* ===========================================================
	Definitions for MLX window properties.
=========================================================== */

# ifndef WIN_TITLE
#  define WIN_TITLE "cub3D - Alex & Leighton"
# endif
# ifndef WIN_WIDTH
#  define WIN_WIDTH 1280
# endif
# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 720
# endif

/* ===========================================================
	Struct declerations.
=========================================================== */

typedef struct e_validator
{
	bool	success;
	size_t	error_count;
	char	**error_messages;
}	t_validator;

typedef struct s_mlx_data
{
	void	*data;
	void	*window;
}	t_mlx;

typedef struct s_cub3D_map_data
{
	size_t	m_width;
	size_t	m_height;
	char	**tiles;
}	t_map;

typedef struct s_cub3d
{
	t_mlx	mlx;
	t_map	*map_data;
}	t_cub3d;

/* ===========================================================
	Function prototypes.
=========================================================== */

// Exit cub3D.

void		exit_free(t_map **data);

// Initialiser.

void		initialise_cub3d(t_cub3d *app, const char *map_filepath);

// Parser.

void		parse_map_file(const char *filepath, t_map **data);
t_validator	new_validator(void);
t_validator	*add_validation_error(t_validator *validator, const char *message);
void		free_validator(t_validator *validator);

// Events.

int			key_press(int keycode, t_cub3d *app);
int			close_mlx_window(t_cub3d *app);

// Utils.

int			open_file(const char *filepath);
void		vfree(size_t count, ...);
char		**str_append2d(char **array, const char *s);

/* ===========================================================
	!! End of file !!
=========================================================== */

#endif
