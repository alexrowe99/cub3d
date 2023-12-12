/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 08:12:31 by lmells            #+#    #+#             */
/*   Updated: 2023/12/12 14:41:42 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bonus/cub3d_bonus.h>

int	update(t_layer *layer, double timestep)
{
	(void)layer;
	(void)timestep;
	return (1);
}

// Set window properties - dimensions, aspect ratio & origin.
// Initialise MLXGE instance - bind cub3d struct and destroy function.
// Create a new window with defined window properties & title.
static inline void	initialise_mlxge_application(t_cub3d *app,
						struct s_display_properties *view_ptr)
{
	t_window	*win;

	view_ptr = set_window_size(WIN_H, 4.0f / 3);
	win = window();
	win->size.width = view_ptr->size.width * 2 + 2;
	mlxge_init(app, destroy_cub3d);
	if (mlxge_create_window(win->size.width, win->size.height, TITLE) < 0)
		return (mlxge_destroy());
}

void	initialise(t_cub3d *app, const char *map_filepath)
{
	struct s_display_properties	view;

	ft_bzero(app, sizeof(t_cub3d));
	initialise_mlxge_application(app, &view);
	if (!parse_map_file(app, map_filepath))
		return (mlxge_destroy());
}
