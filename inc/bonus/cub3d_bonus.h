/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:10:22 by lmells            #+#    #+#             */
/*   Updated: 2023/12/12 18:57:17 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_CUB3D_H
# define BONUS_CUB3D_H

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

# define WIN_H 1024
# define VIEW_H 720
// # define VIEW_H 720
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

typedef struct s_file_contents
{
	int				fd;
	char			**contents;
	size_t			line_count;
	size_t			it;
}	t_file;

typedef struct s_entity
{
	t_v2d			direction;
	t_v2d			position;
	t_v2d			move;
	double			move_speed;
	double			rotation_speed;
	bool			has_moved;
	t_img_quad		*sprite;
}	t_entity;

enum e_map_tile_types
{
	TILE_EMPTY = -1,
	TILE_FLOOR = 1,
	TILE_WALL = 2,
};

typedef struct s_map
{
	int				scale;
	t_dimensions	size;
	int				**tiles;
	t_img_quad		*sprite;
	int				*floor_colour;
	int				*ceiling_colour;
}	t_map;

typedef struct s_world
{
	t_map			map;
	t_entity		player;
}	t_world;

enum s_parse_rgb_id
{
	ID_FLOOR_RGB = 0,
	ID_CEILING_RGB
};

typedef struct s_raycaster
{
	t_v2d			plane;
	double			camera_x;
	t_v2d			ray_direction;
	t_v2i			map_position;
	t_v2d			side_distance;
	t_v2d			delta_distance;
	double			perpendiular_wall_distance;
	t_v2i			step;
	bool			ray_hit;
	int				side;
}	t_raycast;

typedef struct s_cub3d_game
{
	t_layer			*layer;
	t_viewport		*view;
	t_viewport		*minimap;
	t_dimensions	hud_size;
}	t_game;

typedef struct s_cub3d
{
	char			*wall_texture_paths[TEXTURE_COUNT];
	t_game			*game;
	int				rgb[RGB_COUNT];
	t_world			world;
	// t_raycast		raycaster;
}	t_cub3d;

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
bool		parse_map_tiles(t_file *m_file, t_world *world);

// Parser Utils

bool		validate_map_tiles(const char *line);
bool		is_valid_character(int c);
bool		is_spawn_tile(int c, t_entity *player);
int			store_tile(char tile);

// Utils

int			find_middle_value(int a, int b);

#endif
