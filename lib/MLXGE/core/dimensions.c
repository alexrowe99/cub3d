/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dimensions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:42:48 by lmells            #+#    #+#             */
/*   Updated: 2023/10/09 11:43:03 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dimensions.h>

t_dimensions	dimensions(int w, int h)
{
	return ((t_dimensions){.width=w, .height=h});
}
