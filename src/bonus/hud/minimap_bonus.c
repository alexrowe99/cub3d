/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:02:12 by lmells            #+#    #+#             */
/*   Updated: 2023/12/18 10:03:43 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bonus/cub3d_bonus.h>

inline static t_v2d   set_minimap_screen_pos(t_dimensions view,
						t_dimensions hud, t_dimensions win)
{
	int center_win_x;
	int center_hud_y;
	int minimap_start_y;

	center_win_x = find_middle_value(win.width, view.width);
	center_hud_y = find_middle_value(hud.height, view.height);
	minimap_start_y = win.height - hud.height + center_hud_y;
	return (vector_2_double(center_win_x, minimap_start_y));
}

bool	create_minimap(t_hud *hud, t_layer *game_layer, t_dimensions win_size)
{
	t_display	mini_view;

	mini_view = display_properties(256, WIDE_16_9);
	mini_view.origin = set_minimap_screen_pos(mini_view.size, hud->size,
		win_size);
	hud->minimap = mlxge_new_viewport(&game_layer->viewport_list,
		mini_view.origin, mini_view.size);
	if (!hud->minimap)
	{
		cub3d_error("Failed to initialise game viewport because: "
			"Couldn't allocate memory");
		return (false);
	}
	hud->minimap->frame->bg_colour = 0x00FF00;
	return (true);
}

