/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:36:29 by lmells            #+#    #+#             */
/*   Updated: 2023/11/29 16:12:05 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_display.h>

struct s_display_properties	display_properties(size_t height,
								double aspect_ratio)
{
	return ((struct s_display_properties){
		.origin = {0, 0},
		.size = (t_dimensions){height * aspect_ratio, height},
		.aspect_ratio = aspect_ratio
	});
}

struct s_display_properties	*window(void)
{
	static struct s_display_properties	window;

	return (&window);
}

struct s_display_properties	*set_window_size(size_t win_height,
								double aspect_ratio)
{
	struct s_display_properties	*win;

	win = window();
	*win = display_properties(win_height, aspect_ratio);
	return (win);
}
