/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:17:00 by lmells            #+#    #+#             */
/*   Updated: 2023/10/27 21:18:57 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "dimensions.h"

typedef struct s_application_window
{
	t_dimensions	size;
	void			*mlx_win_ptr;
}	t_window;

#endif
