/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxge.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:31:23 by lmells            #+#    #+#             */
/*   Updated: 2023/10/11 16:33:47 by lmells           ###   ########.fr       */
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

void	mlxge_init(void);

int		mlxge_create_window(int width, int height, char *title);

void	*mlxge_new_layer(int frame_width, int frame_height, void *on_update);
void	mlxge_push_layer(t_layer *layer);

void	*mlxge_new_key_event(int type, int code, int (*funct)(), void *param);
void	mlxge_push_event(void *event_ptr, void **event_list_ptr);

int		mlxge_key_down(int keycode);
int		mlxge_key_up(int keycode);

int		mlxge_run(void);

int		mlxge_destroy(void);

void	mlxge_fill_frame(void *frame_ptr, uint32_t colour_rgb);
void	mlxge_draw_circle(void *frame_ptr, int cx, int cy, int radius,
			uint32_t colour_rgb);

#endif
