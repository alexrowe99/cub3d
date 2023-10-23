/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 09:48:10 by lmells            #+#    #+#             */
/*   Updated: 2023/10/21 17:11:11 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGES_H
# define IMAGES_H

# include <images_struct.h>

void	*mlxge_new_image(void **img_list_ptr, int orig_x, int orig_y,
			int size_x, int size_y);
void	mlxge_destroy_images(void *img_list_ptr);
void	mlxge_set_bg_colour(void *img_ptr, int colour_rgb);

#endif
