/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 09:20:02 by lmells            #+#    #+#             */
/*   Updated: 2023/12/13 17:42:34 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "layers.h"

void		mlxge_render(void *mlx_inst, void *mlx_win, t_render_layer *layers);
void		mlxge_fill(t_image *image, int colour);
void		mlxge_fill_rect(t_image *image, t_v2i start, t_v2i end,
				int colour);
t_image	*set_pixels(t_image *frame, t_image *image,
				t_v2d img_origin);
void		put_pixel(t_image *image, int x, int y, int colour);

#endif