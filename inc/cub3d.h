/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:10:22 by lmells            #+#    #+#             */
/*   Updated: 2023/09/06 16:43:46 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libftall.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>

# define RGB_COUNT 2
# define TEXTURE_COUNT 4

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

typedef struct s_cub3d
{
	t_v2i		m_dim;
	char		**map_tiles;
	uint64_t	*rgb_floor_ceiling[RGB_COUNT];
	char		*texture_paths[TEXTURE_COUNT];
	t_v2i		player_spawn;
}	t_cub3d;

bool		cub3d_error(const char *format_message, ...);

// Parser
int			get_texture_id(const char *element);
bool		parse_texture_element(const char *element, size_t id,
				t_cub3d *app);
int			get_rgb_id(const char *element);
bool		parse_rgb_element(const char *element, size_t id, t_cub3d *app);

// Utils
uint64_t	rgb_to_uint64(uint8_t r, uint8_t g, uint8_t b);

#endif
