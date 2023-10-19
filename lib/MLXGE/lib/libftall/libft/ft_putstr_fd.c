/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:32:22 by lmells            #+#    #+#             */
/*   Updated: 2023/10/18 11:57:23 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftall.h"
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	u __attribute__ ((unused));
	
	u = write(fd, s, ft_strlen(s));
}
