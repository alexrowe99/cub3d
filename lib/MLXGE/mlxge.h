/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxge.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:31:23 by lmells            #+#    #+#             */
/*   Updated: 2023/10/13 12:40:12 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLXGE_H
# define MLXGE_H

# include <lib/libftall/libftall.h>
# include <core/layers_struct.h>
# include <core/input.h>

# define BUILD_OS 1

# ifdef BUILD_OS
#  if BUILD_OS == 1
#   define OS_MacOS
# 	include <core/macos_keycodes.h>
#  elif BUILD_OS == 2
#   define OS_Linux
# 	include <core/linux_keycodes.h>
#  else
#   error "OS not yet supported..."
#  endif
# endif

void	mlxge_init(void *app_ptr, int (*app_destructor)(void *app_ptr));

// Pass -width & -height for fullscreen titled window.
int		mlxge_create_window(int width, int height, char *title, bool centered);

void	*mlxge_new_layer(int frame_width, int frame_height, void *on_update);
void	mlxge_push_layer(t_layer *layer);

void	*mlxge_new_key_event(int type, int code, int (*funct)(), void *param);
void	mlxge_push_event(void *event_ptr, void **event_list_ptr);

// Creates and returns a new image.
// Pushes image to front of image list.
void	*mlxge_new_image(void **img_list_ptr, int orig_x, int orig_y,
			int size_x, int size_y);

int		mlxge_key_down(int keycode);
int		mlxge_key_up(int keycode);

int		mlxge_run(void);

int		mlxge_destroy(void);

void	mlxge_center_image(void *img_ptr, void *frame_ptr);
void	mlxge_fill(void *img_ptr, uint32_t colour_rgb);
void	mlxge_draw_circle(void *img_ptr, int cx, int cy, int radius,
			uint32_t colour_rgb);
void	mlxge_draw_rect_fill(void *img_ptr, t_v2i start, t_v2i end,
			uint32_t colour_rgb);

#endif
