/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layers_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:02:45 by lmells            #+#    #+#             */
/*   Updated: 2023/09/23 14:58:52 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAYERS_STRUCTS_H
# define LAYERS_STRUCTS_H

# include <vector.h>
# include <events.h>

# include <stdlib.h>
# include <stdbool.h>

typedef struct s_layer_image
{
	t_v2i				dim;
	t_v2i				orig;
	void				*mlx_img_ptr;
	uint32_t			*pbuff;
	int					pctx[3];
}	t_img;

typedef struct s_layers
{
	bool				is_window_layer;
	t_img				*image;
	t_event_list		*events[COUNT_SUPPORTED_EVENTS];
	bool				updated;
}	t_layer;

typedef struct s_layer_list
{
	t_layer				*layer;
	struct s_layer_list	*next;
}	t_layer_list;

#endif
