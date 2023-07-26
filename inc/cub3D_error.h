/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:57:09 by lmells            #+#    #+#             */
/*   Updated: 2023/07/26 23:23:31 by lmells           ###   ########.fr       */
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
# define MAX_BUFFER 512

/*
	Defined error messages.
*/

# define ERR_INIT_MAP "Could not initialise map data"
# define ERR_PARSE_MAP "Could not parse map file"

/*
	Defined reasons for errors.
*/

# define MEM_ALLOC "memory allocation failed."
# define INVALID_MAP_TILES "invalid map tiles are present."

# define ERR_RGB_PARSE "Could not save rgb colour"
# define RGB_DEFINE_HELP "\nHelp for defining floor & ceiling rgb values in map\
 file!\n  -  The line must start with a single character ('F' for floor, 'C' \
for ceiling).\n  -  Seperate the rgb colour values using whitespace (space or \
tab).\n  -  Each value (r - red, g - green, b - blue) must be in the range of \
0-255 and seperated with ','.\n\n  Example:\n\tF 25,54,220\n"
# define UNKOWN_CHAR "un-recognisable character...\n" RGB_DEFINE_HELP
# define MISSING_VALUES "missing rgb values...\n" RGB_DEFINE_HELP



void	*print_error(const char *message);

#endif
