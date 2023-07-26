/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:57:09 by lmells            #+#    #+#             */
/*   Updated: 2023/07/26 09:51:57 by lmells           ###   ########.fr       */
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

# define ERR_INIT_MAP "Failed to initialise map data"
# define ERR_PARSE_MAP "Failed to parse map data"

/*
	Defined reasons for generic error messages.
*/

# define MEM_ALLOC "memory allocation failed."
# define INVALID_MAP_TILES "invalid map tiles are present."

void	*print_error(const char *message);

#endif
