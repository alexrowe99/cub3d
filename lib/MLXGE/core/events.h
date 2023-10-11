/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:11:52 by lmells            #+#    #+#             */
/*   Updated: 2023/10/11 12:23:10 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include <input.h>

typedef struct s_layer_events_list
{
	void							*layer_ref;
	struct s_layer_events_list		*next;
}	t_event_layer;

enum e_event_type
{
	ON_KEY_PRESS,
	ON_KEY_RELEASE,
	ON_MOUSE_PRESS,
	ON_MOUSE_RELEASE,
	ON_MOUSE_MOVE,
	ON_EXPOSE,
	ON_DESTROY,
	COUNT_EVENT_TYPES
};

enum e_mlx_event_codes
{
	MLX_ON_KEY_PRESS = 2,
	MLX_ON_KEY_RELEASE = 3,
	MLX_ON_MOUSE_PRESS = 4,
	MLX_ON_MOUSE_RELEASE = 5,
	MLX_ON_MOUSE_MOVE = 6,
	MLX_ON_EXPOSE = 12,
	MLX_ON_DESTROY = 17
};

typedef struct s_event_list
{
	int							type;
	int							code;
	int							(*handle_event)(void *);
	void						*event_param;
	struct s_event_list			*next;
}	t_event_list;

void	mlxge_set_mlx_event_hooks(void *mlx_win_ptr, t_event_layer *evnt_lst);
void	**mlxge_new_event_list(void);

int		mlxge_on_keypress_event(int keycode, void *param);
int		mlxge_on_destroy_event(void *param);

void	mlxge_push_event(void *event_ptr, void **event_list_ptr);
void	mlxge_destroy_events(t_event_list **events);

// int		mlxge_key_down(int keycode);
// int		mlxge_key_up(int keycode);

#endif
