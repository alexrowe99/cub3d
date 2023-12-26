/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_core.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:30:38 by lmells            #+#    #+#             */
/*   Updated: 2023/12/26 13:16:31 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_CORE_H
# define RENDER_CORE_H

# include <render/render_queue.h>

typedef struct s_line_y
{
	int	start;
	int	end;
}	t_line;

t_zbuff_node	*new_branch_leaf(t_image **image);
t_zbuff_tree	*create_z_buffer_tree(size_t max_z);
t_zbuff_tree	*resize_z_buffer_tree(t_zbuff_tree *tree, size_t new_max_z);
t_zbuff_tree	*validate_z_buffer_tree(t_zbuff_tree *tree, size_t z_index);
void			push_z_buffer(t_zbuff_tree *tree, size_t z_index,
					t_zbuff_node *new_node);
void			push_image_z_buffer_tree(t_zbuff_tree *tree, t_image **image);
void			destroy_z_buffer_tree(t_zbuff_tree *tree);

#endif