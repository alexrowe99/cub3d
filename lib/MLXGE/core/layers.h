/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layers.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:02:13 by lmells            #+#    #+#             */
/*   Updated: 2023/10/09 14:37:12 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAYERS_H
# define LAYERS_H

# include <layers_struct.h>

typedef struct s_layer_list	t_window_layer;

typedef enum e_list_type
{
	EVENT_LAYER,
	WINDOW_LAYER,
	COUNT_LAYER_LIST_TYPES
}	t_list_type;

void	*mlxge_new_layer(int frame_width, int frame_height, void *on_update);

void	*mlxge_new_frame(int origin_x, int origin_y, int width, int height,
			void *mlx_image);

void	mlxge_push_layer_list_front(t_list_type type, void *layer, void **list);
void	mlxge_destroy_layers(t_list_type type, void *layers);

#endif
