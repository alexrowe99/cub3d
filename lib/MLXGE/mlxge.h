/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxge.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:05:18 by lmells            #+#    #+#             */
/*   Updated: 2023/10/28 20:29:05 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLXGE_H
# define MLXGE_H

# define MACOS 1
# define LINUX 2
# ifndef BUILD_OS
#  define BUILD_OS MACOS
# endif
# ifdef BUILD_OS
#  if BUILD_OS == MACOS
#   include <core/macos_keycodes.h>
#  elif BUILD_OS == LINUX
#   include <core/linux_keycodes.h>
#  else
#   error "OS is not yet supported..."
#  endif
# endif

# include <lib/libftall/libftall.h>
# include <core/events.h>
# include <core/layers.h>
# include <core/dimensions.h>
# include <core/vector.h>

void		mlxge_init(void *app_struct_ptr,
				int (*destroy_app_struct_funct)(void *));
void		mlxge_destroy(void);
int			mlxge_run(void);

int			mlxge_create_window(int width, int height, char *title);

t_layer		*mlxge_new_layer(t_v2i origin, t_dimensions size,
				int (*on_update)(t_layer *));
int			mlxge_push_layer(t_layer *layer);

t_event		*mlxge_new_key_event(enum e_key_input_types input, int keycode,
				int (*handler)(void *param), void *param);
void		mlxge_push_event(t_event *event, t_event **list);

t_viewport	*mlxge_new_viewport(t_viewport **list, t_v2i origin,
				t_dimensions size);

t_img_quad	*mlxge_new_image(t_img_quad **list, t_v2i origin,
				t_dimensions size);
void		mlxge_fill(t_img_quad *image, uint32_t colour);
void		mlxge_draw_circle(t_img_quad *image, t_v2i center, int size,
				uint32_t colour);

#endif
