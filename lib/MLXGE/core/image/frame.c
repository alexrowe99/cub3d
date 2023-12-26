/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 13:21:22 by lmells            #+#    #+#             */
/*   Updated: 2023/12/26 13:21:55 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>

t_image	*mlxge_new_frame(t_v2d origin, t_dimensions size,
				bool is_mlx_object)
{
	return (create_image(origin, size, is_mlx_object));
}
