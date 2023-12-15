/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_buffer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:44:36 by lmells            #+#    #+#             */
/*   Updated: 2023/12/15 16:31:04 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <render/render_core.h>

void	push_image_z_buffer_tree(t_zbuff_tree *tree, t_image **image_addr)
{
	t_image			*image;
	t_zbuff_node	*leaf;

	image = *image_addr;
	leaf = tree->branches[image->z_index];
	if (leaf)
	{
		while (leaf->next)
			leaf = leaf->next;
		leaf->next = new_branch_leaf(image_addr);
	}
	else
		tree->branches[image->z_index] = new_branch_leaf(image_addr);
}

void	mlxge_push_image_z_buffer(t_layer *layer, t_image **image_addr, size_t z_index)
{
	(*image_addr)->z_index = z_index;
	layer->z_buffer_tree = validate_z_buffer_tree(layer->z_buffer_tree, z_index);
	push_image_z_buffer_tree(layer->z_buffer_tree, image_addr);
}
