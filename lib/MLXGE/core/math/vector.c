/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:54:07 by lmells            #+#    #+#             */
/*   Updated: 2023/12/13 11:15:07 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector.h>

t_v2d   vector_2_double(double x, double y)
{
    return ((t_v2d){x, y});
}

t_v2i   vector_2_int(int x, int y)
{
    return ((t_v2i){x, y});
}