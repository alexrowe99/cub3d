/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:57:09 by lmells            #+#    #+#             */
/*   Updated: 2023/07/23 16:59:03 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ERROR_H
# define CUB3D_ERROR_H

/*
	Include unistd for write function and pre processor definiton for stderr fd
	number.
*/

# include <unistd.h>

/*
	Escape codes for coloured text.
*/

# define TEXT_RED "\e[0;91m"
# define TEXT_WHITE "\e[0m"

/*
	Defined max buffer size for printing error message to stderr.
*/
// 	Should probably increase this as messages get more detailed....
//	Could create a file for detailed logs and write to that?
# define MAX_BUFFER 128

/*
	Defined error messages for generic errors.
*/

# define __ERR_MAP_INIT_FAIL__ "Failed to initialise map data"
# define __ERR_MAP_POPTILE_FAIL__ "Could not populate map tiles"

/*
	Defined reasons for generic error messages.
*/

# define __MEM_ALLOC__ "memory allocation failed."
# define __MAP_INVALID__ "map tiles are invalid."

void	*print_error(const char *message);

#endif
