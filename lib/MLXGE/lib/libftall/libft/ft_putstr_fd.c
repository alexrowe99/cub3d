/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:32:22 by lmells            #+#    #+#             */
/*   Updated: 2023/10/27 21:10:41 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftall.h"
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	int u	__attribute__ ((unused));

	u = write(fd, s, ft_strlen(s));
}
