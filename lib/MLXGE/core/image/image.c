/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 08:50:31 by lmells            #+#    #+#             */
/*   Updated: 2023/12/14 16:09:29 by lmells           ###   ########.fr       */
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

// ----- API -------------------------------------------------------------------

t_image	*mlxge_new_image(t_image **list, t_v2d origin,
				t_dimensions size)
{
	t_image	*node;
	t_image	*image;

	image = create_image(origin, size, false);
	if (image)
	{
		mlxge_fill(image, image->bg_colour);
		if (!*list)
		{
			*list = image;
			return (image);
		}
		node = *list;
		while (node->next)
			node = node->next;
		node->next = image;
	}
	return (image);
}

// Z-Index is used as too keep track of drawing order.
// Will error exit program if memory allocation fails.
t_image	*mlxge_new_image_z(t_layer *layer, size_t z_index, t_v2d origin,
			t_dimensions size)
{
	t_image	*image;

	image = create_image(origin, size, false);
	if (image)
	{
		image->z_index = z_index;
		layer->z_buffer_tree = validate_z_buffer_tree(layer->z_buffer_tree, z_index);
		mlxge_log(DEBUG, "Image Ptr = %p", (void *)image);
		push_image_z_buffer_tree(layer->z_buffer_tree, image);
		mlxge_log(DEBUG, "Image Ptr = %p", (void *)layer->z_buffer_tree->branches[image->z_index]->image);
	}
	return (image);
}
