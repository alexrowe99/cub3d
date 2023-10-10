/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:10:22 by lmells            #+#    #+#             */
/*   Updated: 2023/10/10 16:52:55 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libftall.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <stdint.h>

// ----- Window Definitions -----------------------------------------

# define WIDTH 1184
# define HEIGHT 740
# define TITLE "Cub3D Ray-Casting Demo - Alex & Leighton"

// ----- Parser Definitions -----------------------------------------

# define RGB_COUNT 2
# define TEXTURE_COUNT 4

// ----- Build Requirements For Parsrer ------------------------------

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

typedef struct s_vec2_int
{
	int			x;
	int			y;
}	t_v2i;

typedef struct s_vec2_double
{
	double		x;
	double		y;
}	t_v2d;

typedef struct s_entity
{
	t_v2i		spawn;
	t_v2i		spawn_direction;
}	t_entity;

typedef struct s_cub3d
{
	t_v2i		m_dim;
	char		**map_tiles;
	uint32_t	*rgb_floor_ceiling[RGB_COUNT];
	char		*texture_paths[TEXTURE_COUNT];
	t_entity	player;
}	t_cub3d;

bool		cub3d_error(const char *format_message, ...);
void		destory_cub3d(t_cub3d *app);

// Parser
void		parse_map_file(t_cub3d *app, const char *filepath);
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

// Vector
t_v2i		v2i(int x, int y);
t_v2i		v2d_to_v2i(t_v2d e);
t_v2d		v2d(double x, double y);
t_v2d		v2i_to_v2d(t_v2i e);

#endif
