/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:10:22 by lmells            #+#    #+#             */
/*   Updated: 2023/12/13 17:42:34 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// ----- Headers ----------------------------------------------------

# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <math.h>

# include <mlxge.h>
# include <cub3d_file_struct.h>
# include <cub3d_display.h>

// ----- Window definitions -----------------------------------------

# define WIN_H 720
# define TITLE "Cub3D Ray-Casting Demo - Alex & Leighton"

// ----- Parser definitions -----------------------------------------

# define RGB_COUNT 2
# define TEXTURE_COUNT 4

// ----- Build requirements for parsrer ------------------------------

# ifndef BUILD_MANDATORY
#  define BUILD_MANDATORY
# endif
# ifdef BUILD_MANDATORY
#  define COUNT_ELEMENTS 6
# endif

enum e_map_tile_types
{
	TILE_EMPTY = -1,
	TILE_FLOOR = 1,
	TILE_WALL = 2,
};

enum s_parse_rgb_id
{
	ID_FLOOR_RGB = 0,
	ID_CEILING_RGB
};

typedef struct s_entity
{
	t_v2d			direction;
	t_v2d			position;
	t_v2d			move;
	double			move_speed;
	double			rotation_speed;
	bool			has_moved;
}	t_entity;

typedef struct s_map
{
	int				scale;
	t_dimensions	size;
	int				**tiles;
	t_image		*sprite;
	int				*floor_colour;
	int				*ceiling_colour;
}	t_map;

typedef struct s_world
{
	t_map			map;
	t_entity		player;
}	t_world;

typedef struct s_cub3d
{
	int				rgb[RGB_COUNT];
	char			*wall_texture_paths[TEXTURE_COUNT];
	t_world			world;
}	t_cub3d;

typedef struct s_map_file	t_file;

t_cub3d		*cub3d(void);
void		initialise(t_cub3d *app, const char *map_filepath);
bool		cub3d_error(const char *format_message, ...);
int			destroy_cub3d(t_cub3d *app);

// Parser

bool		parse_map_file(t_cub3d *app, const char *filepath);
int			get_texture_id(const char *element);
bool		parse_texture_element(const char *element, size_t id,
				t_cub3d *app);
int			get_rgb_id(const char *element);
bool		parse_rgb_element(const char *element, size_t id, t_cub3d *app);
bool		parse_map_tiles(t_file *file, t_world *world);

// Parser Utils

bool		validate_map_tiles(const char *line);
bool		is_valid_character(int c);
bool		is_spawn_tile(int c, t_entity *player);
int			store_tile(char tile);

// Utils

int			find_middle_value(int a, int b);

#endif
