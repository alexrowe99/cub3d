/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:06:23 by lmells            #+#    #+#             */
/*   Updated: 2023/11/03 10:24:56 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# define MACOS 1
# define LINUX 2
# ifndef BUILD_OS
#  define BUILD_OS LINUX
# endif
# ifdef BUILD_OS
#  if BUILD_OS == MACOS
// #   include <macos_keycodes.h>
#   include <../lib/mlx/mac/mlx.h>
#  elif BUILD_OS == LINUX
// #   include <linux_keycodes.h>
#   include <../lib/mlx/linux/mlx.h>
#  else
#   error "OS is not yet supported..."
#  endif
# endif

# include <sys/time.h> // REMOVE ME ILLEGAL! Debugging purposes only... ;)

# include <stdio.h>
# include <stdbool.h>
# include <../lib/libftall/libftall.h>
# include <log.h>
# include <window.h>
# include <layers.h>
# include <events.h>
# include <render.h>
# include <vector.h>
# include <key_input.h>

typedef struct s_global_time
{
	struct timeval	start;
	struct timeval	end;
	double			elapsed_sec;
	double			since_last_print;
}	t_gtime;

typedef int(*t_destroy_app)(void *);
struct s_user_app
{
	void				*user_app_ref;
	t_destroy_app		user_app_destroy;
};

typedef struct s_mlxge_core
{
	void				*mlx_inst_ptr;
	t_window			*mlx_window;
	struct s_user_app	*sandbox;
	t_render_layer		*render_layers;
	t_event_layer		*event_layers;
	t_gtime				timer;
}	t_mlxge;

t_mlxge			*get_core(void);
void			mlxge_destroy(void);

t_layer			*create_window_layer(t_dimensions size);
t_layer			*mlxge_new_layer(t_v2i origin, t_dimensions size,
					int (*on_update)(t_layer *));
int				mlxge_push_layer(t_layer *layer);
void			mlxge_destroy_layers(t_layer *list);

t_img_quad		*mlxge_new_frame(t_v2i origin, t_dimensions size,
					bool is_mlx_object);
t_img_quad		*mlxge_new_image(t_img_quad **list, t_v2i origin,
					t_dimensions size);

t_event_layer	*mlxge_load_event_layers(t_layer *render_list);
int				mlxge_handle_destroy_events(t_event_layer *layers_list);
void			mlxge_load_mlx_event_hooks(void *mlx_win_ptr,
					t_event_layer *event_layers);

void			*map_mlx_keycodes(t_key_input *keyboard);
int				mlxge_handle_key_press_events(int keycode, t_event_layer *list);
int				mlxge_handle_key_release_events(int keycode,
					t_event_layer *list);
void			mlxge_destroy_event_layers(t_event_layer *list);

void			mlxge_output_ppm(t_img_quad *image);

t_key_input		*mlxge_keyboard(void);

#endif
