/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_queue.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:15:55 by lmells            #+#    #+#             */
/*   Updated: 2023/12/18 14:50:17 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_QUEUE_H
# define RENDER_QUEUE_H

# include "../image_struct.h"

typedef struct s_z_buffer_node
{
	int						z_index;
	bool					node_allocated_image;
	t_image					**image_ref;
	struct s_z_buffer_node	*next;
}	t_zbuff_node;

typedef struct s_z_buffer_tree
{
	int						z_range;
	t_zbuff_node			**branches;
}	t_zbuff_tree;

#endif
