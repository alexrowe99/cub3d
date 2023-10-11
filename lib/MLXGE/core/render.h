/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:34:10 by lmells            #+#    #+#             */
/*   Updated: 2023/10/09 11:51:56 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

#include <layers.h>

typedef struct s_mlxge_layer_frame	t_frame;

int		mlxge_render(t_layer *layers);

#endif
