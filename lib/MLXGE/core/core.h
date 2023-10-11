/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:10:17 by lmells            #+#    #+#             */
/*   Updated: 2023/10/11 14:13:40 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "mlx.h"
# include <libftall.h>
# include <stdio.h>
# include <stdbool.h>

# include <events.h>
# include <layers.h>
# include <input.h>
# include <dimensions.h>

# ifdef BUILD_OS
#  if BUILD_OS == 1
#   define OS_MacOS
# 	include <macos_keycodes.h>
#  elif BUILD_OS == 2
#   define OS_Linux
# 	include <linux_keycodes.h>
#  else
#   error "OS not yet supported..."
#  endif
# endif

# define ERR_FAIL_INIT "Failed to initialise MLXGE becuase"
# define ERR_WIN_FAIL "Failed to create MLXGE window because"
# define ERR_EVNT_FAIL "Failed to create MLXGE event because"
# define ERR_LAYER_FAIL "Failed to create MLXGE layer because"

#define MLX_MEM_FAIL "MiniLibX couldn't allocate memory"

// ----- Logging System --------------------------------------------------------

#define PREF_FATAL "\e[0;91m[ MLXGE_FATAL_ERROR ]"
#define PREF_ERR "\e[0;91m[ MLXGE_ERROR ]\e[0m"
#define PREF_WARN "\e[0;93m[ MLXGE_WARNING ]\e[0m"
#define PREF_DBG "\e[0;96m[ MLXGE_DEBUG ]\e[0m"
#define PREF_INFO "\e[0;92m[ MLXGE_INFO ]\e[0m"
#define NL "\n\e[0m"

enum e_log_levels
{
	INFO,
	DEBUG,
	WARNING,
	ERROR,
	FATAL,
	COUNT_LOG_LEVELS
};

struct s_mlxge_log
{
	bool	init;
	char	*prefix[COUNT_LOG_LEVELS];
};

void			mlxge_log(int lvl, const char *fmt, ...);

// -----------------------------------------------------------------------------

struct s_mlxge
{
	void					*mlx;
	struct s_mlxge_window	*win;
	void					*layers;
	void					*event_layer;
};

struct s_mlxge	*get_mlxge_core(void);
int				mlxge_destroy(void);

// ----- Window ----------------------------------------------------------------

struct s_mlxge_window
{
	void			*id_ptr; // Could potentiallly make a list of windows and implement a manager.
	t_dimensions	dim;
	void			*img;
	void			*layer;
};

int				mlxge_create_window(int width, int height, char *title);
void			*mlxge_window_layer(int frame_width, int frame_height,
					void *on_update, void *mlx_img_ptr);
void			mlxge_destroy_window(void *mlx_ptr, void *win_ptr);
int				mlxge_update(void);

// -----------------------------------------------------------------------------

// ----- Typedefs --------------------------------------------------------------

typedef int(*t_on_update)(struct s_layer_list *);
typedef struct s_layer_list	t_layer;
typedef t_event_list		t_event;

void			*mlxge_new_key_event(int type, int code, int (*funct)(),
						void *param);
void			*mlxge_load_events_layers(t_layer **layers);
int				mlxge_render(t_layer *layers);

// -----------------------------------------------------------------------------

#endif
