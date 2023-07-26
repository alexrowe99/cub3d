/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:53:04 by lmells            #+#    #+#             */
/*   Updated: 2023/07/25 12:29:09 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_validation	new_validator(void)
{
	t_validation	validator;

	ft_bzero(&validator, sizeof(t_validation));
	return (validator);
}

void	free_validator(t_validation *validator)
{
	while (validator->error_count--)
	{
		if (validator->error_messages[validator->error_count])
			free(validator->error_messages[validator->error_count]);
	}
	if (validator->error_messages)
		free(validator->error_messages);
}

t_validation	*add_validation_error(t_validation *validator, const char *message)
{
	const char	*add_message_fail;

	add_message_fail = "Could not add a new error message : " MEM_ALLOC;
	if (!message || !*message)
		return (validator);
	validator->caught_error = true;
	validator->error_messages = str_append2d(validator->error_messages,
			message);
	if (!validator->error_messages)
		print_error(add_message_fail);
	else
		validator->error_count++;
	return (validator);
}

void	validation_exit(t_validation *validation, t_map **data)
{
	size_t	i;

	i = 0;
	if (validation->caught_error && validation->error_count)
	{
		while (i < validation->error_count)
			print_error(validation->error_messages[i++]);
	}
	free_validator(validation);
	exit_free(data);
}
