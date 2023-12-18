/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 08:50:31 by lmells            #+#    #+#             */
/*   Updated: 2023/12/18 15:47:33 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <render/render_core.h>

t_image	*new_image(void)
{
	t_image	*image;

	image = ft_calloc(1, sizeof(t_image));
	if (!image)
	{
		mlxge_log(ERROR, "Failed to create MLXGE image quad because : "\
			"Couldn't allocate memory");
		return ((void *)0);
	}
	image->z_index = -1;
	return (image);
}

static t_image	*create_image(t_v2d origin, t_dimensions size,
						bool is_mlx_object)
{
	t_image	*image;

	image = new_image();
	if (!image)
		return ((void *)0);
	image->bg_colour = 0xFF000000;
	image->origin = origin;
	image->size = size;
	if (!is_mlx_object)
	{
		image->buff = malloc((size.width * size.height + 1) * sizeof(int));
		if (!image->buff)
		{
			mlxge_log(ERROR, "Failed to create MLXGE image quad because : "\
				"Couldn't allocate memory");
			free(image);
			return ((void *)0);
		}
	}
	image->is_mlx_object = is_mlx_object;
	return (image);
}

t_image	*mlxge_new_frame(t_v2d origin, t_dimensions size,
				bool is_mlx_object)
{
	return (create_image(origin, size, is_mlx_object));
}

void	mlxge_destroy_image(t_image *image)
{
	void	*mlx_instance;

	if (image)
	{
		mlx_instance = get_core()->mlx_inst_ptr;
		if (image->is_mlx_object && image->mlx_ptr)
		{
			mlx_destroy_image(mlx_instance, image->mlx_ptr);
			free(image);
			return ;
		}
		if (image->buff)
			free(image->buff);
		free(image);
	}
	image = (void *)0;
}

// ----- API -------------------------------------------------------------------

// Creates a new image and pushes to the layer's z buffer at z_index 0.
// Z-Index is used as too keep track of drawing order.
// Will error exit program if memory allocation fails.
// Returns the image pointer it creates.
t_image	*mlxge_new_image(t_layer *layer, t_v2d origin, t_dimensions size)
{
	t_zbuff_node	*new;

	layer->z_buffer_tree = validate_z_buffer_tree(layer->z_buffer_tree, 0);
	new = new_branch_leaf(0);
	*new->image_ref = create_image(origin, size, false);
	if (!*new->image_ref)
	{
		free(new->image_ref);
		free(new);
		mlxge_destroy();
	}
	mlxge_fill(*new->image_ref, (*new->image_ref)->bg_colour);
	push_z_buffer(layer->z_buffer_tree, 0, new);
	return (*new->image_ref);
}

// Creates a new image and pushes to the layer's z buffer at the specified z_index.
// Z-Index is used as too keep track of drawing order.
// Will error exit program if memory allocation fails.
// Returns the image pointer it creates.
t_image	*mlxge_new_image_z(t_layer *layer, size_t z_index, t_v2d origin,
			t_dimensions size)
{
	t_zbuff_node	*new;

	layer->z_buffer_tree = validate_z_buffer_tree(layer->z_buffer_tree, z_index);
	new = new_branch_leaf(0);
	*new->image_ref = create_image(origin, size, false);
	if (!*new->image_ref)
	{
		free(new->image_ref);
		free(new);
		mlxge_destroy();
	}
	mlxge_fill(*new->image_ref, (*new->image_ref)->bg_colour);
	push_z_buffer(layer->z_buffer_tree, z_index, new);
	return (*new->image_ref);
}
