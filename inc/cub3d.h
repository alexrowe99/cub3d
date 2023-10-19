/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:10:22 by lmells            #+#    #+#             */
/*   Updated: 2023/10/17 14:49:39 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// ----- C standard library headers ---------------------------------

# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>

// ----- External library headers -----------------------------------

# include <mlxge.h>

// ----- Window definitions -----------------------------------------

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
	t_v2d		pos;
	t_v2i		direction;
	double		velocity;
	bool		has_moved;
}	t_entity;

typedef struct s_cub3d
{
	t_dimensions	map_dim;
	char			**map_tiles;
	size_t			tile_size;
	uint32_t		*rgb_floor_ceiling[RGB_COUNT];
	char			*texture_paths[TEXTURE_COUNT];
	t_entity		player;
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

// Colour
uint32_t	rgb_to_uint32(uint8_t r, uint8_t g, uint8_t b);

#endif
