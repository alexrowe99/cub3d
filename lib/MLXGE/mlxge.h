/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxge.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:31:23 by lmells            #+#    #+#             */
/*   Updated: 2023/10/21 17:15:34 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLXGE_H
# define MLXGE_H

# include <lib/libftall/libftall.h>
# include <core/layers_struct.h>
# include <core/input.h>
# include <core/vector.h>

# define OS_MacOS 1
# define OS_Linux 2
# ifndef BUILD_OS
#  define BUILD_OS OS_MacOS
# endif
# ifdef BUILD_OS
#  if BUILD_OS == OS_MacOS
# 	include <core/macos_keycodes.h>
#  elif BUILD_OS == OS_Linux
# 	include <core/linux_keycodes.h>
#  else
#   error "OS not yet supported..."
#  endif
# endif

void			mlxge_init(void *app_ptr, int (*app_destructor)(void *app_ptr));

// Pass -width & -height for fullscreen titled window.
int				mlxge_create_window(int width, int height, char *title);
t_dimensions	mlxge_window_dimensions(void);

void			*mlxge_new_layer(int frame_width, int frame_height, void *on_update);
void			mlxge_push_layer(t_layer *layer);

void			*mlxge_new_key_event(int type, int code, int (*funct)(), void *param);
void			mlxge_push_event(void *event_ptr, void **event_list_ptr);

// Creates and returns a new image.
// Pushes image to front of image list.
void			*mlxge_new_image(void **img_list_ptr, int orig_x, int orig_y,
					int size_x, int size_y);
void			mlxge_set_bg_colour(void *img_ptr, int colour_rgb);

int				mlxge_key_down(int keycode);
int				mlxge_key_up(int keycode);

int				mlxge_run(void);
int				mlxge_destroy(void);

void			mlxge_move_frame_center_window(void *frame_ptr);
void			mlxge_move_image_center_frame(void *img_ptr, void *frame_ptr);
void			mlxge_image_translate(void *img_ptr, int offset_x, int offset_y);

void			mlxge_fill(void *img_ptr, uint32_t colour_rgb);
void			mlxge_draw_circle(void *img_ptr, int cx, int cy, int radius,
					int colour_rgb);
void			mlxge_draw_rect_fill(void *img_ptr, t_v2i start, t_v2i end,
					int colour_rgb);

#endif
