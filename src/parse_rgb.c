/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 19:02:15 by lmells            #+#    #+#             */
/*   Updated: 2023/08/31 19:06:13 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	get_rgb_id(const char *line)
{
	int	rgb_id;

	rgb_id = -1;
	if (!ft_strncmp(line, "F ", 2))
		rgb_id = 0;
	else if (!ft_strncmp(line, "C ", 2))
		rgb_id = 1;
	return (rgb_id);
}

static char	**validate_rgb_data(const char *data_str, void *id)
{
	static void	*check_id;
	char		**value_strs;

	if (!check_id)
		check_id = id;
	else if (check_id == id)
	{
		cub3d_error("Invalid parse: Duplicate RGB setting \"%s\"", data_str);
		return (NULL);
	}
	check_id = id;
	value_strs = ft_split(data_str + 2, ',');
	if (ft_2d_array_len(value_strs) != 3)
	{
		cub3d_error("Invalid parse: Missing required RGB values "\
		"\"%s\"", data_str);
		ft_free_str_2d(value_strs, 0);
		value_strs = NULL;
	}
	return (value_strs);
}

static bool	store_rgb_values(const char *data_str, int id, t_cub3d *app)
{
	bool		error;
	char		**rgb_values;
	ssize_t		i;
	int			rgb[3];

	rgb_values = validate_rgb_data(data_str, &app->rgb_floor_ceiling[id]);
	error = !rgb_values;
	i = -1;
	while (!error && ++i < 3)
	{
		rgb[i] = ft_atoi(rgb_values[i]);
		if (rgb[i] < 0 || 255 < rgb[i])
			error = cub3d_error("Invalid parse: RGB value out of range 0-255 "\
			"\"%s\"", data_str);
	}
	if (!error)
		app->rgb_floor_ceiling[id] = rgb_to_uint64(rgb[0], rgb[1], rgb[2]);
	ft_free_str_2d(rgb_values, 0);
	return (!error);
}

bool	parse_rgb(t_file *map_file, t_cub3d *app, size_t rgb_count)
{
	bool	error;
	int		rgb_id;

	error = false;
	while (!error && rgb_count--)
	{
		rgb_id = get_rgb_id(map_file->contents[map_file->it]);
		if (rgb_id < 0)
			return (!cub3d_error("Invalid parse: Unrecognisable RGB setting "\
					"\"%s\"", map_file->contents[map_file->it]));
		error = !store_rgb_values(map_file->contents[map_file->it], rgb_id,
				app);
		if (error && errno)
			return (!cub3d_error("Something unexcpected happend"));
		map_file->it++;
	}
	return (!error);
}
