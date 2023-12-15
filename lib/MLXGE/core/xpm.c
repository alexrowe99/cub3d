/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:45:15 by lmells            #+#    #+#             */
/*   Updated: 2023/12/13 18:06:53 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <image/image.h>
#include <fcntl.h>

t_dimensions    get_image_dimensions_from_file(const char *xpm_filepath)
{
    int             fd;
    t_dimensions    image_size;

    image_size = (t_dimensions){0};
    fd = open(xpm_filepath, O_RDONLY, 0400);
    if (fd < 0)
    {
        mlxge_destroy();
    }
    return (image_size);
}

t_image	*mlxge_load_xpm_image(const char *xpm_filepath)
{
    t_image *xpm;
    intfd;

    xpm = new_image();
    if (xpm)
    {
        xpm->size = get_image_dimensions_from_file(xpm_filepath);
        xpm->is_mlx_object = true;
        xpm->mlx_ptr = 
    }
    return (xpm);
}
