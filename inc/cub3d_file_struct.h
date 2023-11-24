/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_file_struct.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 09:34:18 by lmells            #+#    #+#             */
/*   Updated: 2023/11/24 09:38:08 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_FILE_STRUCT_H
# define CUB3D_FILE_STRUCT_H

# include <stdlib.h>

struct s_map_file
{
	int		fd;
	char	**contents;
	size_t	line_count;
	size_t	it;
};

#endif
