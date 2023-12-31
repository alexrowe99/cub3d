/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 09:52:44 by lmells            #+#    #+#             */
/*   Updated: 2023/11/06 19:11:09 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <viewport.h>

#define ERR_VIEW_CREAT "Failed to create a new MLXGE viewport because"

static inline t_viewport	*new_view(void)
{
	t_viewport	*view;

	view = ft_calloc(1, sizeof(t_viewport));
	if (!view)
		mlxge_log(ERROR, ERR_VIEW_CREAT" : Couldn't allocate memory");
	return (view);
}

static inline void	push_viewport_list_back(t_viewport *view, t_viewport **list)
{
	t_viewport	*node;

	node = *list;
	if (!node)
	{
		*list = view;
		return ;
	}
	while (node->next)
		node = node->next;
	node->next = view;
}

void	mlxge_destroy_viewports(t_viewport *viewport_list)
{
	t_img_quad	*image;
	t_viewport	*node;

	node = viewport_list;
	while (node)
	{
		viewport_list = viewport_list->next;
		if (node->camera)
			free(node->camera);
		if (node->images_to_render)
		{
			image = node->images_to_render;
			node->images_to_render = node->images_to_render->next;
			mlxge_destroy_image_quad(image);
		}
		if (node->frame)
			mlxge_destroy_image_quad(node->frame);
		free(node);
		node = viewport_list;
	}
}

// ----- API -------------------------------------------------------------------

t_viewport	*mlxge_new_viewport(t_viewport **list, t_v2d origin,
				t_dimensions size)
{
	t_viewport	*view;

	view = new_view();
	if (!view)
		return ((void *)0);
	view->frame = mlxge_new_frame(origin, size, false);
	if (!view->frame)
	{
		mlxge_log(ERROR, ERR_VIEW_CREAT" : There is no update frame to draw "\
			"graphics");
		free(view);
		return ((void *)0);
	}
	push_viewport_list_back(view, list);
	return (view);
}

t_cam_ortho2d	*mlxge_new_camera_2d_orthographic(t_v2i origin)
{
	t_cam_ortho2d	*camera;

	camera = ft_calloc(1, sizeof(t_cam_ortho2d));
	if (!camera)
	{
		mlxge_log(ERROR, "Failed to create a new MLXGE 2D orthographic camera "\
			"because : Couldn't allocate memory");
		return ((void *)0);
	}
	camera->origin = origin;
	return (camera);
}
