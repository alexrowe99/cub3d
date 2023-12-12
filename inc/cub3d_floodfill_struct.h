/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_floodfill_struct.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:30:01 by lmells            #+#    #+#             */
/*   Updated: 2023/12/12 14:31:14 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_FLOODFILL_STRUCT_H
# define CUB3D_FLOODFILL_STRUCT_H

# include <mlxge.h>

typedef struct s_floodfill_map_validation
{
	t_dimensions	dim;
	int				**grid;
	bool			*visited;
}	t_ffill;

#endif