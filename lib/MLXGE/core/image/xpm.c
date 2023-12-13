/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:45:15 by lmells            #+#    #+#             */
/*   Updated: 2023/12/13 20:31:05 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <image/image.h>

t_image	*mlxge_load_xpm_image(const char *xpm_filepath)
{
	t_image	*xpm;

	xpm = new_image();
	if (xpm)
	{
		xpm->is_mlx_object = true;
		xpm->mlx_ptr = mlx_xpm_file_to_image(get_core()->mlx_inst_ptr,
			(char *)xpm_filepath, &xpm->size.width, &xpm->size.height);
		if (!xpm->mlx_ptr)
		{
			mlxge_log(ERROR, "Couldn't load xpm file using MiniLibX");
			mlxge_destroy();
		}
		xpm->buff = (int *)mlx_get_data_addr(xpm->mlx_ptr, &xpm->ctx[0],
			&xpm->ctx[1], &xpm->ctx[2]);
	}
	return (xpm);
}
