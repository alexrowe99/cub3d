/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:57:50 by lmells            #+#    #+#             */
/*   Updated: 2023/10/04 11:35:52 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>

static struct s_mlxge_log	*logger(void)
{
	static struct s_mlxge_log	logger;

	if (!logger.init)
	{
		logger = (struct s_mlxge_log){
			.prefix = {PREF_INFO, PREF_DBG, PREF_WARN, PREF_ERR, PREF_FATAL},
			.init = true
		};
	}
	return (&logger);
}

void	mlxge_log(int lvl, const char *fmt, ...)
{
	char	*message;
	va_list	vargs;

	message = NULL;
	va_start(vargs, fmt);
	if (ft_vasprintf(&message, fmt, vargs) < 0)
		exit(fprintf(stderr, PREF_FATAL" : LOG FAILURE... EXITING PROCESS!"NL));
	va_end(vargs);
	ft_printf("%s\t: %s"NL, logger()->prefix[lvl], message);
	free(message);
}
