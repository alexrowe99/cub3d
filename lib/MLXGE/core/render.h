/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:34:10 by lmells            #+#    #+#             */
/*   Updated: 2023/10/22 20:05:55 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

#include <layers.h>
#include <images_struct.h>

typedef t_image	t_frame;

int			mlxge_render(t_layer *layers);
void		redraw_frame(t_frame *frame, t_image *img_list, t_viewport *viewport);
uint32_t	*set_pixels(t_frame *frame, uint32_t *img_buff, t_v2i img_origin,
				t_dimensions img_size);

#endif
