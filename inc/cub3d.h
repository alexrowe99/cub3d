/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:10:22 by lmells            #+#    #+#             */
/*   Updated: 2023/08/29 13:56:15 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libftall.h>
# include <stdbool.h>

typedef struct	s_file_contents
{
	int		fd;
	char	**contents;
	size_t	line_count;
}	t_fcontent;

typedef struct s_vec2_int
{
	int	x;
	int	y;
}	t_v2i;

typedef struct s_cub3d
{
	char	*texture_paths[4];
	t_v2i	m_dim;
}	t_cub3d;

#endif
