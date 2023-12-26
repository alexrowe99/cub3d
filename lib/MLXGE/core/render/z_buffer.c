/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_buffer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:44:36 by lmells            #+#    #+#             */
/*   Updated: 2023/12/26 13:15:51 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <render/render_core.h>

void	push_image_z_buffer_tree(t_zbuff_tree *tree, t_image **image)
{
	t_zbuff_node	*leaf;

	leaf = tree->branches[(*image)->z_index];
	if (leaf)
	{
		while (leaf->next)
			leaf = leaf->next;
		leaf->next = new_branch_leaf(image);
	}
	else
	{
		tree->branches[(*image)->z_index] = new_branch_leaf(image);
		leaf = tree->branches[(*image)->z_index];
	}
}

void	mlxge_push_image_z_buffer(t_image **image, size_t z_index,
			t_layer *layer)
{
	(*image)->z_index = z_index;
	layer->z_buffer_tree = validate_z_buffer_tree(layer->z_buffer_tree,
			z_index);
	push_image_z_buffer_tree(layer->z_buffer_tree, image);
}

void	push_z_buffer(t_zbuff_tree *tree, size_t z_index,
			t_zbuff_node *new_node)
{
	t_zbuff_node	*leaf;

	leaf = tree->branches[z_index];
	if (!leaf)
	{
		tree->branches[z_index] = new_node;
		return ;
	}
	while (leaf->next)
		leaf = leaf->next;
	leaf->next = new_node;
}
