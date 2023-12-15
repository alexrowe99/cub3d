/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_buffer_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:44:36 by lmells            #+#    #+#             */
/*   Updated: 2023/12/14 16:15:22 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>

t_zbuff_node	**create_tree_branches(size_t branch_count)
{
	t_zbuff_node	**branches;

	branches = ft_calloc(branch_count, sizeof(t_zbuff_node *));
	if (!branches)
	{
		mlxge_log(ERROR, "Failed to create a new z buffer tree because: "\
			"Couldn't allocate memory");
		mlxge_destroy();
	}
	return (branches);
}

t_zbuff_node	*new_branch_leaf(t_image *image)
{
	t_zbuff_node	*leaf;

	leaf = ft_calloc(1, sizeof(t_zbuff_node));
	if (!leaf)
	{
		mlxge_log(ERROR, "Failed to create new z_buffer branch leaf because: "\
			"Couldn't allocate memory");
		mlxge_destroy();
	}
	leaf->image = image;
	leaf->z_index = image->z_index;
	return (leaf);
}

t_zbuff_tree	*create_z_buffer_tree(size_t max_z)
{
	t_zbuff_tree	*tree;

	tree = ft_calloc(1, sizeof(t_zbuff_tree));
	if (tree)
	{
		tree->z_range = max_z + 1;
		tree->branches = create_tree_branches(max_z + 1);
	}
	return (tree);
}

t_zbuff_tree	*resize_z_buffer_tree(t_zbuff_tree *tree, size_t new_max_z)
{
	size_t			i;
	t_zbuff_node	**new_branches;

	i = 0;
	new_branches = create_tree_branches(new_max_z + 1);
	while (i < tree->z_range)
	{
		new_branches[i] = tree->branches[i];
		i++;
	}
	free(tree->branches);
	tree->branches = new_branches;
	tree->z_range = new_max_z + 1;
	return (tree);
}

t_zbuff_tree	*validate_z_buffer_tree(t_zbuff_tree *tree, size_t z_index)
{
	if (!tree)
		tree = create_z_buffer_tree(z_index);
	else if (z_index >= tree->z_range)
		tree = resize_z_buffer_tree(tree, z_index);
	return (tree);
}
