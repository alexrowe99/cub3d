/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:20:15 by lmells            #+#    #+#             */
/*   Updated: 2023/10/12 12:12:35 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>

// bit shift by keycode % 8
// index by keycode / 8
static char	*input(void)
{
	static char	bitfield[33];

	return (bitfield);
}

void	set_key_input_poll(int keycode)
{
	input()[keycode/8] = 1 << keycode % 8;
}

void	remove_key_input_poll(int keycode)
{
	input()[keycode/8] = 0 << keycode % 8;
}

// ----- API -------------------------------------------------------------------

int	mlxge_key_down(int keycode)
{
	return (input()[keycode / 8] >> keycode % 8 & 0x1);
}

int	mlxge_key_up(int keycode)
{
	return ((input()[keycode / 8] >> keycode % 8) == 0);
}
