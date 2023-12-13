/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:21:46 by lmells            #+#    #+#             */
/*   Updated: 2023/12/13 17:37:11 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bonus/cub3d_bonus.h>

void	create_hud_display(t_hud *hud, t_dimensions win, int offset_y)
{
	hud->size = dimension_2d(win.width, win.height - offset_y);
    hud->origin = vector_2_double(0, offset_y);

    // hud->background_image = mlxge_load_xpm_image();
}

t_hud	*create_hud(t_game *game, t_window *win,
            struct s_display_properties *game_view)
{
    game->hud = ft_calloc(1, sizeof(t_hud));
    if (!game->hud)
    {
        cub3d_error("Failed to create HUD because: Couldn't allocate memory");
        return ((void *)0);
    }
    create_hud_display(game->hud, win->size, game_view->size.height);
    if (!create_minimap(game->hud, game->layer, win->size))
    {
        free(game->hud);
        game->hud = (void *)0;
    }
    return (game->hud);
}