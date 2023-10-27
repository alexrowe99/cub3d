/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:00:24 by lmells            #+#    #+#             */
/*   Updated: 2023/10/25 10:14:15 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_H
# define LOG_H

# define PREF_INFO "\e[0;92m"
# define PREF_DEBUG "\e[0;96m"
# define PREF_WARNING "\e[0;93m"
# define PREF_ERROR "\e[0;91m"

enum e_log_levels
{
	INFO,
	DEBUG,
	WARNING,
	ERROR,
	COUNT_LOG_LEVELS
};

void	mlxge_log(enum e_log_levels lvl, const char *format, ...);

#endif
