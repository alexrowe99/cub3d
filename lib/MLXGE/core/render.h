/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 09:20:02 by lmells            #+#    #+#             */
/*   Updated: 2023/10/28 20:29:05 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "layers.h"

void		mlxge_render(void *mlx_inst, void *mlx_win, t_render_layer *layers);
void		mlxge_fill(t_img_quad *image, uint32_t colour);
t_img_quad	*set_pixels(t_img_quad *frame, t_img_quad *image);

#endif