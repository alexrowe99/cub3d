/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map_validator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:53:04 by lmells            #+#    #+#             */
/*   Updated: 2023/07/23 16:56:01 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_validator	new_validator(void)
{
	t_validator	validator;

	ft_bzero(&validator, sizeof(t_validator));
	return (validator);
}

void	free_validator(t_validator *validator)
{
	while (validator->error_count--)
	{
		if (validator->error_messages[validator->error_count])
			free(validator->error_messages[validator->error_count]);
	}
	if (validator->error_messages)
		free(validator->error_messages);
}

t_validator	*add_validation_error(t_validator *validator, const char *message)
{
	const char	*add_message_fail;

	add_message_fail = "Could not add a new error message : " __MEM_ALLOC__;
	if (!message || !*message)
		return (validator);
	validator->success = false;
	validator->error_messages = str_append2d(validator->error_messages,
			message);
	if (!validator->error_messages)
		print_error(add_message_fail);
	else
		validator->error_count++;
	return (validator);
}
