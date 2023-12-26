/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 13:14:48 by lmells            #+#    #+#             */
/*   Updated: 2023/12/26 13:32:24 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <key_input.h>
#include <core.h>

t_key_input	*mlxge_keyboard(void)
{
	static t_key_input	*keyboard;

	if (!keyboard)
	{
		keyboard = ft_calloc(1, sizeof(t_key_input));
		if (!keyboard || !map_mlx_keycodes(keyboard))
		{
			mlxge_log(ERROR, "Failed to initialise MLXGE keyboard inputs "\
				"because : Couldn't allocate memory");
			mlxge_destroy();
		}
	}
	return (keyboard);
}

// ----- API -------------------------------------------------------------------

bool	mlxge_is_key_down(enum e_mlxge_keycodes code)
{
	return (mlxge_keyboard()->input[code].is_down);
}
