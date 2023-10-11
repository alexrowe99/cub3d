/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 11:19:33 by lmells            #+#    #+#             */
/*   Updated: 2023/08/23 12:58:10 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_core.h>

char	*get_flag_info(char *fp, t_flag *info)
{
	if (*fp == '0')
	{
		while (*fp == '0')
			fp++;
		info->type = PAD_ZEROS;
		info->pad_len = ft_atoi(fp);
		fp += get_unsigned_len_base(info->pad_len, 10);
	}
	return (fp);
}
