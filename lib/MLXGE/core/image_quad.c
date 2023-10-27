/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_quad.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 08:50:31 by lmells            #+#    #+#             */
/*   Updated: 2023/10/27 20:55:18 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <image_quad.h>

static inline t_img_quad	*new_image_quad(void)
{
	t_img_quad	*image;

	image = ft_calloc(1, sizeof(t_img_quad));
	if (!image)
	{
		mlxge_log(ERROR, "Failed to create MLXGE image quad because : "\
			"Couldn't allocate memory");
		return ((void *)0);
	}
	return (image);
}

static t_img_quad	*create_image_quad(t_v2i origin, t_dimensions size,
						bool is_mlx_object)
{
	t_img_quad	*image;

	image = new_image_quad();
	if (!image)
		return ((void *)0);
	image->bg_colour = 0xFF000000;
	image->origin = origin;
	image->size = size;
	if (!is_mlx_object)
	{
		image->buff = malloc((size.width * size.height + 1) * sizeof(uint32_t));
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

t_img_quad	*mlxge_new_frame(t_v2i origin, t_dimensions size,
				bool is_mlx_object)
{
	return (create_image_quad(origin, size, is_mlx_object));
}

void	mlxge_destroy_image_quad(t_img_quad *image)
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

t_img_quad	*mlxge_new_image(t_v2i origin, t_dimensions size)
{
	return (create_image_quad(origin, size, false));
}
