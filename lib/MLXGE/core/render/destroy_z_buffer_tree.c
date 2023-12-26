/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_z_buffer_tree.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:44:36 by lmells            #+#    #+#             */
/*   Updated: 2023/12/26 13:16:17 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render/render_core.h>
#include <stdio.h>

void	destory_tree_leaves(t_zbuff_node *leaf)
{
	t_zbuff_node	*dead;

	while (leaf)
	{
		dead = leaf;
		leaf = leaf->next;
		if (*dead->image_ref)
		{
			mlxge_destroy_image(*dead->image_ref);
			*dead->image_ref = (void *)0;
		}
		if (dead->node_allocated_image)
			free(dead->image_ref);
		free(dead);
	}
}

void	destroy_z_buffer_tree(t_zbuff_tree *tree)
{
	t_zbuff_node	*leaf;

	if (tree)
	{
		while (tree->z_range--)
		{
			leaf = tree->branches[tree->z_range];
			destory_tree_leaves(leaf);
		}
		free(tree->branches);
		free(tree);
		tree = (void *)0;
	}
}
