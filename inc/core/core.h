/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:08:09 by lmells            #+#    #+#             */
/*   Updated: 2023/09/23 12:32:06 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include <mlx.h>
# include <layers_structs.h>
# include <stdbool.h>
# include <stdio.h>

# define FATAL_ERROR "\e[0;91mEngine Fatal Error\e[0m:\n"

typedef struct s_mlx_instance
{
	void			*inst;
	void			*win;
	bool			running;
	void			*win_img;
}	t_mlx_inst;

typedef struct s_engine_core
{
	t_mlx_inst		*mlx;
	t_layer_list	*render_layers;
	t_layer_list	*event_layers;
	void			*app_ref;
	int				(*app_dtor)(void *);
	int				(*app_update)(void *);
}	t_core;

t_core	*get_engine(void);
int		engine_destroy(void);

bool	engine_error(const char *message);
void	engine_warning(const char *message);
void	engine_info(const char *message);
void	engine_debug(const char *message);

int		engine_handle_keypress(int keycode, void *param);
int		engine_handle_mouse_event(int code, int x, int y, void *param);

#endif
