/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parser_rgb.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:33:32 by lmells            #+#    #+#             */
/*   Updated: 2023/07/28 00:35:44 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	rgb_store_index(char c)
{
	if (c == 'F')
		return (FLOOR_RGB);
	if (c == 'C')
		return (CEILING_RGB);
	return (COUNT_RGB_PARSE);
}

t_initialiser	*parse_rgb_value(char *parse_line, t_rgb *colour,
	t_initialiser *init)
{
	size_t	i;
	char	**values;

	values = ft_split(parse_line, ',');
	i = 0;
	while (values[i])
		i++;
	if (i == 3 && ft_isdigit(*values[0]) && ft_isdigit(*values[1])
		&& ft_isdigit(*values[2]))
	{
		colour->r = ft_atoi(values[0]);
		colour->g = ft_atoi(values[1]);
		colour->b = ft_atoi(values[2]);
	}
	else if (i == 3 && (!ft_isdigit(*values[0]) || !ft_isdigit(*values[1])
			||!ft_isdigit(*values[2])))
		add_validation_error(&init->validation,
			ERR_PARSE_MAP" : "ERR_RGB_PARSE" : "UNKOWN_CHAR);
	else
		add_validation_error(&init->validation,
			ERR_PARSE_MAP" : "ERR_RGB_PARSE" : "MISSING_VALUES);
	while (i--)
		free(values[i]);
	free(values);
	return (init);
}

t_initialiser	*validate_rgb_range(t_rgb *colours, t_initialiser *init)
{
	size_t	i;

	i = 0;
	while (i < COUNT_RGB_PARSE)
	{
		if ((colours[i].r < 0 || 255 < colours[i].r)
			&& (colours[i].g < 0 || 255 < colours[i].g)
			&& (colours[i].b < 0 || 255 < colours[i].b))
		{
			add_validation_error(&init->validation,
				ERR_PARSE_MAP" : "ERR_RGB_PARSE" : "VALUE_OUT_OF_RANGE);
			break ;
		}
		i++;
	}
	return (init);
}