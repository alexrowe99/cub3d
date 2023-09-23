/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layers.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:02:45 by lmells            #+#    #+#             */
/*   Updated: 2023/09/23 12:38:09 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAYERS_H
# define LAYERS_H

# include <vector.h>
# include <libftall.h>

# include <layers_structs.h>

t_layer			*engine_new_layer(void);
void			engine_destroy_layer(t_layer *layer);
void			engine_destroy_layer_list(t_layer_list **head);

t_layer_list	*engine_new_layer_list_node(void);
int				engine_push_layer_list(t_layer *layer, t_layer_list **list);

#endif
