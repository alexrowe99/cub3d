/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:16:11 by lmells            #+#    #+#             */
/*   Updated: 2023/12/26 13:32:10 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <key_input.h>
#include <core.h>
#include <fcntl.h>

static char	*get_keycode_filepath(char *cwd, char *target, char *filename)
{
	char	*keycode_filepath;
	char	*relative_path;
	size_t	cwd_len;

	if (!cwd)
	{
		mlxge_log(ERROR, "Couldn't get the current working directory");
		return ((void *)0);
	}
	cwd_len = ft_strlen(cwd);
	if (ft_strncmp(cwd, target, cwd_len))
	{
		mlxge_log(ERROR, "Target path is not located in current working "\
			"directory");
		mlxge_log(DEBUG, "CWD = \"\"; TARGET = \"%s\"", cwd, target);
		return ((void *)0);
	}
	relative_path = ft_strjoin("./", ft_strchr(target + cwd_len, '/') + 1);
	free(target);
	if (!relative_path)
		mlxge_log(ERROR, "Failed to get relative path because : "\
			"Couldn't allocate memory");
	keycode_filepath = ft_strjoin(relative_path, filename);
	free(relative_path);
	return (keycode_filepath);
}

static int	open_mlxge_keycodes_os(char *mlxge_path)
{
	char	cwd[FILENAME_MAX];
	char	*keycodes_filepath;
	int		keycode_fd;

	if (!mlxge_path)
	{
		mlxge_log(ERROR, "MLXGE target path was not define during build "\
			"process");
		return (-1);
	}
	keycodes_filepath = get_keycode_filepath(getcwd(cwd, sizeof(cwd)),
			ft_strjoin(mlxge_path, "/core/"), MLX_KEYCODE_FILE);
	if (!keycodes_filepath)
		return (-1);
	mlxge_log(DEBUG, "MLXGE KEYCODE FILE RELATIVE PATH = \"%s\"",
		keycodes_filepath);
	keycode_fd = open(keycodes_filepath, O_RDONLY, 0666);
	if (keycode_fd < 0)
		mlxge_log(ERROR, "Couldn't open file \"%s\"", keycodes_filepath);
	free(keycodes_filepath);
	return (keycode_fd);
}

// Read keys in and store them in respective array position.
// When loading mlx hooks. Loop over array and pass a pointer to the
// specific array index.
// Then should have thie index for the corresponding keycode.
// Can use this to poll input and handle events.

static inline void	get_codes_from_file(t_key_input *keyboard, int keycodes_fd,
						int *track_key_count)
{
	char		*line;
	char		*evaluate_line;

	line = get_next_line(keycodes_fd);
	while (line)
	{
		evaluate_line = ft_strtrim(line, "\t\n");
		free(line);
		if (!ft_strncmp("MLX_KEY", evaluate_line, ft_strlen("MLX_KEY")))
		{
			keyboard->input[*track_key_count].code = ft_atoi(
					ft_strrchr(evaluate_line, ' '));
			if ((*track_key_count)++ == COUNT_TRACKED_KEYCODES)
			{
				mlxge_log(WARNING, "Keycode count exceeds limit... No longer "\
					"getting codes.");
				free(evaluate_line);
				break ;
			}
		}
		free(evaluate_line);
		line = get_next_line(keycodes_fd);
	}
	close(keycodes_fd);
}

void	*map_mlx_keycodes(t_key_input *keyboard)
{
	int	keycodes_fd;
	int	track_key_count;

	keycodes_fd = open_mlxge_keycodes_os(FULL_PATH_MLXGE);
	if (keycodes_fd < 0)
	{
		free(keyboard);
		return ((void *)0);
	}
	track_key_count = 0;
	get_codes_from_file(keyboard, keycodes_fd, &track_key_count);
	if (track_key_count > COUNT_TRACKED_KEYCODES)
	{
		mlxge_log(ERROR, "Failed to read MiniLibX keycodes because : "\
			"Too many codes in file.");
		free(keyboard);
		keyboard = (void *)0;
	}
	return ((void *)keyboard);
}
