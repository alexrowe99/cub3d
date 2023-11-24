/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 19:02:15 by lmells            #+#    #+#             */
/*   Updated: 2023/11/03 11:54:20 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	get_rgb_id(const char *element)
{
	int	rgb_id;

	rgb_id = -1;
	if (!ft_strncmp(element, "F ", 2))
		rgb_id = 0;
	else if (!ft_strncmp(element, "C ", 2))
		rgb_id = 1;
	return (rgb_id);
}

static char	**validate_rgb(const char *data_str, int *store)
{
	char	**value_strs;

	if (store)
	{
		cub3d_error("Invalid parse: Duplicate RGB setting \"%s\"", data_str);
		return (NULL);
	}
	value_strs = ft_split(data_str + 2, ',');
	if (ft_2d_array_len(value_strs) != 3)
	{
		cub3d_error("Invalid parse: RGB setting \"%s\" requires 3 values "\
		"[0-255]", data_str);
		ft_free_str_2d(value_strs, 0);
		value_strs = NULL;
	}
	return (value_strs);
}

bool	parse_rgb_element(const char *element, size_t id, t_cub3d *app)
{
	bool		error;
	char		**rgb_values;
	ssize_t		i;
	int			rgb[3];

	rgb_values = validate_rgb(element, app->rgb[id]);
	error = !rgb_values;
	i = -1;
	while (!error && ++i < 3)
	{
		rgb[i] = ft_atoi(rgb_values[i]);
		if (rgb[i] < 0 || 255 < rgb[i])
			error = cub3d_error("Invalid parse: RGB setting \"%s\" value out "\
					"of range 0-255 ", element);
	}
	ft_free_str_2d(rgb_values, 0);
	if (!error)
	{
		app->rgb[id] = malloc(sizeof(int));
		if (!app->rgb[id])
			return (!cub3d_error("something unexpected happened"));
		*app->rgb[id] = (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
	}
	return (!error);
}
