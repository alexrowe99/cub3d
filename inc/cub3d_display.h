/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_display.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 09:34:18 by lmells            #+#    #+#             */
/*   Updated: 2023/12/19 08:21:11 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DISPLAY_H
# define CUB3D_DISPLAY_H

# include <mlxge.h>

struct s_display_properties
{
	t_v2d			origin;
	t_dimensions	size;
	double			aspect_ratio;
};

typedef struct s_display_properties	t_window;
typedef struct s_display_properties	t_display;

t_window					*window(void);
t_window					*set_window_size(size_t win_height,
								double aspect_ratio);
struct s_display_properties	display_properties(size_t height,
								double aspect_ratio);


#endif
