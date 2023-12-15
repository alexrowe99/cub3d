/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxge.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:05:18 by lmells            #+#    #+#             */
/*   Updated: 2023/12/15 16:35:20 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLXGE_H
# define MLXGE_H

// # define MACOS 1
// # define LINUX 2
// # ifndef BUILD_OS
// #  define BUILD_OS MACOS
// # endif
// # ifdef BUILD_OS
// #  if BUILD_OS == MACOS
// #   include <core/macos_keycodes.h>
// #  elif BUILD_OS == LINUX
// #   include <core/linux_keycodes.h>
// #  else
// #   error "OS is not yet supported..."
// #  endif
// # endif

# include <lib/libftall/libftall.h>
# include <core/events.h>
# include <core/layers.h>
# include <core/dimensions.h>
# include <core/vector.h>
# include <core/key_input.h>

void			mlxge_init(void *app_struct_ptr,
					int (*destroy_app_struct_funct)());
void			mlxge_destroy(void);
int				mlxge_run(void);

int				mlxge_create_window(int width, int height, char *title);

t_layer			*mlxge_new_layer(t_v2d origin, t_dimensions size,
					int (*on_update)(t_layer *, double));
int				mlxge_push_layer(t_layer *layer);

bool			mlxge_is_key_down(enum e_mlxge_keycodes code);
t_event			*mlxge_new_key_event(enum e_key_input_types input, int keycode,
					int (*handler)(void *param), void *param);
void			mlxge_push_event(t_event *event, t_event **list);

t_viewport		*mlxge_new_viewport(t_viewport **list, t_v2d origin,
					t_dimensions size);
t_cam_ortho2d	*mlxge_new_camera_2d_orthographic(t_v2i offset);

t_image			*mlxge_new_image(t_image **list, t_v2d origin,
					t_dimensions size);
t_image			*mlxge_new_image_z(t_layer *layer, size_t z_index, t_v2d origin,
					t_dimensions size);
void			mlxge_push_image_z_buffer(t_layer *layer, t_image **image,
					size_t z_index);
void			mlxge_output_ppm(t_image *image);
t_image			*mlxge_load_xpm_image(const char *xpm_filepath);

void			mlxge_fill(t_image *image, int colour);
void			mlxge_draw_circle(t_image *image, t_v2i center, int radius,
					int colour);
void			mlxge_fill_rect(t_image *image, t_v2i start, t_v2i end,
					int colour);
void			mlxge_draw_vertical_line(t_image *image, int x, t_v2i y_line,
					int colour);

#endif
