/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:23:39 by lmells            #+#    #+#             */
/*   Updated: 2023/07/26 23:26:33 by lmells           ###   ########.fr       */
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

# include "cub3d_error.h"

# include <stdio.h>
# include <stdbool.h>
# include <stdarg.h>

/* ===========================================================
	Debug definition to avoid intellisense errors.
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
	Enumerations definitions.
=========================================================== */

enum e_map_tile_types
{
	MAP_TILE_NONE = 0,
	MAP_TILE_EMPTY = ' ',
	MAP_TILE_FLOOR = '0',
	MAP_TILE_WALL = '1',
	MAP_TILE_SPAWN_NORTH = 'N',
	MAP_TILE_SPAWN_SOUTH = 'S',
	MAP_TILE_SPAWN_EAST = 'E',
	MAP_TILE_SPAWN_WEST = 'W',
	MAP_TILE_VALIDATE_FLOOR = '#'
};

enum e_data_index
{
	DATA_TEXTURE,
	DATA_RGB,
	DATA_MAP,
	COUNT_DATA_INDEX
};

typedef enum e_map_texture_type
{
	NORTH_WALL,
	SOUTH_WALL,
	EAST_WALL,
	WEST_WALL,
	COUNT_TEXTURE_TYPES
}	t_texture_type;

// FC - Floor & Ceiling.

typedef enum e_parser_functions
{
	TEXTURE_PATHS,
	FC_RGB_VALUES,
	MAP_TILES,
	COUNT_PARSER_FUNCTIONS
}	t_parse;

enum e_store_rgb_values
{
	FLOOR_RGB,
	CEILING_RGB,
	COUNT_RGB_PARSE
};

/* ===========================================================
	Struct definitions.
=========================================================== */

typedef struct s_map_file
{
	char			**data;
	size_t			line_count;
}	t_file;

typedef struct s_validation
{
	bool			caught_error;
	size_t			error_count;
	char			**error_messages;
}	t_validation;

typedef struct s_map_tile
{
	char			type;
	bool			visited;
}	t_map_tile;

typedef struct s_rgb
{
	int				r;
	int				g;
	int				b;
}	t_rgb;

typedef struct s_cub3D_map_data
{
	size_t			map_width;
	size_t			map_height;
	t_map_tile		**tiles;
	char			*texture_paths[COUNT_TEXTURE_TYPES];
	t_rgb			rgb[COUNT_RGB_PARSE];
}	t_map;

typedef struct s_initialiser
{
	bool			*error;
	t_validation	validation;
}	t_initialiser;

typedef struct s_mlx_data
{
	void			*data;
	void			*window;
}	t_mlx;

typedef struct s_cub3d
{
	t_mlx			mlx;
	t_map			*map_data;
}	t_cub3d;

/* ===========================================================
	Function prototypes.
=========================================================== */

// Exit cub3D.

void			exit_free(t_map **data);

// Initialiser.

void			initialise_cub3d(t_cub3d *app, const char *map_filepath);

// Map File.

void			*free_file_data(t_file **file);
t_file			*get_map_file_contents(const char *filepath,
					t_initialiser *init);

// Map Parser.

t_initialiser	*parse_map_data(t_file *map_file, t_map **data,
					t_initialiser *init);
void			parse_wall_texture_path(char **info, size_t *row_offset,
					t_map **data, t_initialiser *init);
t_texture_type	texture_type(char c);
bool			has_texture_header(const char *s);
bool			*validate_texture_paths(size_t *row_offset, t_map **data,
					t_validation *validation);
void			parse_floor_ceiling_rgb_values(char **info, size_t *row_offset,
					t_map **data, t_initialiser *init);
size_t			rgb_store_index(char c);
t_initialiser	*parse_rgb_value(char *parse_line, t_rgb *colour,
					t_initialiser *init);

// Parse textures.

// void			parse_wall_texture_path(char **info, size_t *row_offset,
// 					t_map **data, t_initialiser *init);

// Parse floor and ceiling rgb values.

// void			parse_floor_ceiling_rgb_values(char **info, size_t *row_offset,
// 					t_map **data, t_initialiser *init);

// Validator.

t_validation	new_validator(void);
t_validation	*add_validation_error(t_validation *validator,
					const char *message);
void			free_validator(t_validation *validator);
void			validation_exit(t_validation *validation, t_map **data);

// Events.

int				key_press(int keycode, t_cub3d *app);
int				close_mlx_window(t_cub3d *app);

// Utils.

void			vfree(size_t count, ...);
char			**str_append2d(char **array, const char *s);

/* ===========================================================
	!! End of file !!
=========================================================== */

#endif
