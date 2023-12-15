/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_queue.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:15:55 by lmells            #+#    #+#             */
/*   Updated: 2023/12/14 14:34:20 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_QUEUE_H
# define RENDER_QUEUE_H

# include "../image_struct.h"

typedef struct s_z_buffer_node
{
	size_t					z_index;
	t_image					*image;
	struct s_z_buffer_node	*next;
}	t_zbuff_node;

typedef struct s_z_buffer_tree
{
	size_t					z_range;
	t_zbuff_node			**branches;
}	t_zbuff_tree;



#endif
