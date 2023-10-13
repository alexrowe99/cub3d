/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:34:10 by lmells            #+#    #+#             */
/*   Updated: 2023/10/13 11:13:25 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

#include <layers.h>
#include <images_struct.h>

typedef t_image	t_frame;

int		mlxge_render(t_layer *layers);

#endif
