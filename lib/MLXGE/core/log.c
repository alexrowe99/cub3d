/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:57:48 by lmells            #+#    #+#             */
/*   Updated: 2023/10/25 11:23:08 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>

static inline void	get_log_prefix(int lvl, char **prefix)
{
	if (lvl == INFO)
		*prefix = PREF_INFO"{ MLXGE_INFO }";
	else if (lvl == DEBUG)
		*prefix = PREF_DEBUG"{ MLXGE_DEBUG }";
	else if (lvl == WARNING)
		*prefix = PREF_WARNING"{ MLXGE_WARNING }";
	else if (lvl == ERROR)
		*prefix = PREF_ERROR"{ MLXGE_ERROR }";
}

void	mlxge_log(enum e_log_levels lvl, const char *format, ...)
{
	va_list	ap;
	char	*fmt_output;
	char	*log_prefix;

	fmt_output = 0;
	log_prefix = 0;
	va_start(ap, format);
	ft_vasprintf(&fmt_output, format, ap);
	va_end(ap);
	get_log_prefix(lvl, &log_prefix);
	ft_printf("%s\e[0m: %s.\n", log_prefix, fmt_output);
	free(fmt_output);
}
