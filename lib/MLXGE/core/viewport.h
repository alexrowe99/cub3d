/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:54:30 by lmells            #+#    #+#             */
/*   Updated: 2023/10/27 09:51:28 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEWPORT_H
# define VIEWPORT_H

# include "dimensions.h"
# include "image_quad.h"

typedef struct s_viewport
{
	t_img_quad					*frame;
	struct s_image_quad_list	*images_to_render;
	struct s_viewport			*next;
}	t_viewport;

#endif
