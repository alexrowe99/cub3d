/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_ppm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:41:12 by lmells            #+#    #+#             */
/*   Updated: 2023/12/13 17:42:34 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

static inline int	open_create_output_ppm(const char *parent_dir,
						char **filepath)
{
	char		*err_msg;
	struct stat	st;
	static int	i;
	int			out_fd;

	errno = 0;
	err_msg = 0;
	if (stat(parent_dir, &st) == -1)
	{
		mlxge_log(INFO, "Directory not found \"%s\""\
			": Creating new directory", parent_dir);
		mkdir(parent_dir, 0755);
	}
	ft_asprintf(filepath, "%s/image_%i.ppm", parent_dir, ++i);
	out_fd = open(*filepath, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (out_fd < 0)
	{
		ft_asprintf(&err_msg, PREF_ERROR"{ MLXGE_ERROR }\e[0m: "\
			"Failed to open file \"%s\"", *filepath);
		perror(err_msg);
		free(err_msg);
	}
	return (out_fd);
}

static inline void	write_ppm3_header(t_dimensions size, int out_fd,
						char *filepath)
{
	char	*filename;

	filename = ft_strrchr(filepath, '/') + 1;
	dprintf(out_fd, "# %s\n\n", filename);
	dprintf(out_fd, "P3\n");
	dprintf(out_fd, "%i %i\n", size.width, size.height);
	dprintf(out_fd, "%i\n", 255);
	free(filepath);
}

static inline void	write_pixels(t_image *image, int out_fd)
{
	int			x;
	int			y;
	int			colour;
	__uint8_t	rgb[3];

	y = -1;
	while (++y < image->size.height)
	{
		x = -1;
		while (++x < image->size.width)
		{
			colour = image->buff[y * image->size.width + x];
			rgb[0] = colour >> 16 & 0xFF;
			rgb[1] = colour >> 8 & 0xFF;
			rgb[2] = colour & 0xFF;
			dprintf(out_fd, "%i %i %i ", rgb[0], rgb[1], rgb[2]);
		}
		dprintf(out_fd, "\n");
	}
}

void	mlxge_output_ppm(t_image *image)
{
	int			out_fd;
	char		*out_filepath;
	const char	*out_dirirectory;

	out_filepath = 0;
	out_dirirectory = "./output_ppm/";
	out_fd = open_create_output_ppm(out_dirirectory, &out_filepath);
	if (out_fd < 0)
		return ;
	write_ppm3_header(image->size, out_fd, out_filepath);
	write_pixels(image, out_fd);
	close(out_fd);
}
