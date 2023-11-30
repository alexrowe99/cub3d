/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:26:24 by lmells            #+#    #+#             */
/*   Updated: 2023/11/03 10:18:34 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_INPUT_H
# define KEY_INPUT_H

# define OS_MACOS 1
# define OS_LINUX 2
# ifndef BUILD_OS
#  define BUILD_OS OS_LINUX
# endif
# ifdef BUILD_OS
#  if BUILD_OS == OS_MACOS
#   include "macos_keycodes.h"
#  elif BUILD_OS == OS_LINUX
#   include "linux_keycodes.h"
#  else
#   error "OS is not supported!"
#  endif
# endif

# include <stdlib.h>
# include <stdbool.h>

enum e_mlxge_keycodes
{
	KEY_ESCAPE,
	KEY_BACKTICK,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_0,
	KEY_MINUS,
	KEY_EQUALS,
	KEY_BACKSPACE,
	KEY_SLASH_FORWARD,
	KEY_SQUAREBRACKET_RIGHT,
	KEY_SQUAREBRACKET_LEFT,
	KEY_P,
	KEY_O,
	KEY_I,
	KEY_U,
	KEY_Y,
	KEY_T,
	KEY_R,
	KEY_E,
	KEY_W,
	KEY_Q,
	KEY_TAB,
	KEY_CAPSLOCK,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_SEMICOLON,
	KEY_QUOTE,
	KEY_ENTER,
	KEY_SHIFT_RIGHT,
	KEY_SLASH_BACKWARD,
	KEY_PERIOD,
	KEY_COMMA,
	KEY_M,
	KEY_N,
	KEY_B,
	KEY_V,
	KEY_C,
	KEY_X,
	KEY_Z,
	KEY_SHIFT_LEFT,
	KEY_ALT_LEFT,
	KEY_CONTROL_LEFT,
	KEY_SPACEBAR,
	KEY_CONTROL_RIGHT,
	KEY_ALT_RIGHT,
	KEY_ARROW_LEFT,
	KEY_ARROW_UP,
	KEY_ARROW_DOWN,
	KEY_ARROW_RIGHT,
	COUNT_TRACKED_KEYCODES
};

struct s_key_input_map
{
	int			code;
	bool		is_down;
};

typedef struct s_key_input
{
	struct s_key_input_map	input[COUNT_TRACKED_KEYCODES];
}	t_key_input;

#endif
