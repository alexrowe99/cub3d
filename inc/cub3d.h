/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:10:22 by lmells            #+#    #+#             */
/*   Updated: 2023/11/02 13:39:21 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// ----- Headers ----------------------------------------------------

# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>

# include <mlxge.h>

// ----- Window definitions -----------------------------------------

# define WIN_H 600
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
	int			fd;
	char		**contents;
	size_t		line_count;
	size_t		it;
}	t_file;

typedef struct s_entity
{
	t_v2d		pos;	// Relateive to world space - mapped between (-1 -> 1)
	t_v2i		direction;
	double		velocity;
	bool		has_moved;
}	t_entity;

typedef struct s_world
{
	t_cam_ortho2d	*player_camera;
	t_dimensions	size;
	size_t			scale;
}	t_world;

enum s_generated_textures
{
	PLAYER_TEXTURE,
	MAP_TEXTURE,
	COUNT_GENERATED_TEXTURES
};

typedef struct s_cub3d
{
	t_world			world;
	t_dimensions	map_dim;
	char			**map_tiles;
	size_t			tile_size;
	uint32_t		*rgb_floor_ceiling[RGB_COUNT];
	char			*texture_paths[TEXTURE_COUNT];
	t_entity		player;
	t_img_quad		*textures[COUNT_GENERATED_TEXTURES];
}	t_cub3d;

t_cub3d		*cub3d(void);
void		initialise(t_cub3d *app, const char *map_filepath);
bool		cub3d_error(const char *format_message, ...);
int			destroy_cub3d(void *app_ptr);

// Parser

bool		parse_map_file(t_cub3d *app, const char *filepath);
int			get_texture_id(const char *element);
bool		parse_texture_element(const char *element, size_t id,
				t_cub3d *app);
int			get_rgb_id(const char *element);
bool		parse_rgb_element(const char *element, size_t id, t_cub3d *app);
bool		parse_map_tiles(t_file *m_file, t_cub3d *app);

// Parser Utils

bool		validate_map_tiles(const char *line);
bool		is_valid_character(int c);
bool		is_spawn_tile(int c, t_entity *player);

// Debug

bool		define_debug_scene(t_cub3d *app, t_viewport *debug_view);
t_img_quad	*draw_map_texture(t_cub3d *app, t_viewport *debug_view);

#endif
