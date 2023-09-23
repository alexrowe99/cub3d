/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:03:50 by lmells            #+#    #+#             */
/*   Updated: 2023/09/23 13:43:54 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ===== Engine API ============================================================

#ifndef ENGINE_H
# define ENGINE_H

# include <mlx.h>
# include <libftall.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <errno.h>

# include <vector.h>
# include <layers_structs.h>

// ----- Core ------------------------------------------------------------------

int				engine_init(size_t width, size_t height, const char *title);
void			engine_bind_application(void *application_ptr,
					int (*destructor)(void *), int (*update_loop)(void *));
int				engine_start_application(void);
int				engine_destroy(void);

// ----- Layers ----------------------------------------------------------------

t_layer			*engine_new_layer(void);
t_layer_list	*engine_new_layer_list_node(void);
void			engine_destroy_layer(t_layer *layer);
void			engine_destroy_layer_list(t_layer_list **list);
int				engine_push_layer_list(t_layer *layer, t_layer_list **list);
t_layer_list	*engine_get_render_layers_list(void);
t_layer_list	*engine_get_event_layers_list(void);

// ----- Events ----------------------------------------------------------------

void			engine_push_event_list_back(t_event_list *event_node,
					t_event_list **list);
t_key_event		*engine_new_keypress_event(int keycode, int (*func)(),
					void *param);
t_mouse_event	*engine_new_mousepress_event(int code, t_v2i *bounds,
					int (*event_action)(int button, void *param), void *param);
t_v2i			*engine_set_event_bounds(t_v2i orig, t_v2i size);

// ----- Csketch (graphics) ----------------------------------------------------

void			engine_render_csketch(void);
void			engine_csketch_fill(uint32_t *pixels, size_t w, size_t h,
					uint32_t colour);
void			engine_redraw_csketch(void);

#endif
