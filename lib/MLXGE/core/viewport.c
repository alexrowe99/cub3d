/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 09:52:44 by lmells            #+#    #+#             */
/*   Updated: 2023/10/27 10:59:43 by lmells           ###   ########.fr       */
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

// ----- API -------------------------------------------------------------------

t_viewport	*mlxge_new_viewport(t_viewport **list, int origin_x, int origin_y,
				int view_width, int view_height)
{
	t_viewport	*view;

	view = new_view();
	if (!view)
		return ((void *)0);
	view->frame = mlxge_new_frame(origin_x, origin_y, view_width, view_height,
					false);
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
