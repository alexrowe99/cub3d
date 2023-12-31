/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:54:30 by lmells            #+#    #+#             */
/*   Updated: 2023/11/02 18:16:15 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEWPORT_H
# define VIEWPORT_H

# include "dimensions.h"
# include "image_quad.h"

typedef struct s_2d_orthographic_camera
{
	t_v2i	origin;
	t_v2d	position;
}	t_cam_ortho2d;

typedef struct s_viewport
{
	t_cam_ortho2d				*camera;
	t_img_quad					*frame;
	struct s_image_quad_list	*images_to_render;
	struct s_viewport			*next;
}	t_viewport;

void	mlxge_destroy_viewports(t_viewport *viewport_list);

#endif
