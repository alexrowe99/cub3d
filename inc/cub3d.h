/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:10:22 by lmells            #+#    #+#             */
/*   Updated: 2023/08/31 19:05:35 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libftall.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>

# define TEXTURE_COUNT 4
# define RGB_COUNT 2

typedef struct s_file_contents
{
	int		fd;
	char	**contents;
	size_t	line_count;
	size_t	it;
}	t_file;

typedef struct s_vec2_int
{
	int	x;
	int	y;
}	t_v2i;

typedef struct s_cub3d
{
	t_v2i		m_dim;
	uint64_t	rgb_floor_ceiling[RGB_COUNT];
	char		*texture_paths[TEXTURE_COUNT];
}	t_cub3d;

bool		cub3d_error(const char *format_message, ...);

// Parser
bool		parse_textures_paths(t_file *map, t_cub3d *app,
				size_t texture_count);
bool		parse_rgb(t_file *map_file, t_cub3d *app, size_t rgb_count);

// Utils
uint64_t	rgb_to_uint64(uint8_t r, uint8_t g, uint8_t b);

#endif
