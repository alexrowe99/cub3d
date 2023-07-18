/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:47:37 by lmells            #+#    #+#             */
/*   Updated: 2023/07/18 15:32:54 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*append_str(char *s1, char *s2)
{
	ssize_t	i;
	ssize_t	s1_len;
	ssize_t	s2_len;
	char	*append;

	if (!s2)
		return (s1);
	s1_len = ft_strlen_gnl(s1);
	s2_len = ft_strlen_gnl(s2);
	append = ft_calloc_gnl(s1_len + s2_len + 1, 1);
	if (!append)
		return (NULL);
	i = -1;
	if (s1)
	{
		while (++i < s1_len)
			append[i] = s1[i];
		free(s1);
	}
	i = -1;
	while (++i < s2_len)
		append[i + s1_len] = s2[i];
	return (append);
}

static char	*read_file_and_fill_reserve(int fd, char *reserve)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = ft_calloc_gnl(BUFFER_SIZE + 1, 1);
	if (!buffer)
		return ((char *)ft_free_gnl((void **)&reserve));
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr_gnl(reserve, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		reserve = append_str(reserve, buffer);
	}
	free(buffer);
	if (bytes_read == -1)
		return ((char *)ft_free_gnl((void **)&reserve));
	return (reserve);
}

static char	*remove_extracted_line(char *reserve, char *nl)
{
	char	*tmp_reserve;
	size_t	tmp_reserve_len;

	if (!nl)
		return ((char *)ft_free_gnl((void **)&reserve));
	tmp_reserve_len = (nl - reserve) + 1;
	if (!reserve[tmp_reserve_len])
		return ((char *)ft_free_gnl((void **)&reserve));
	tmp_reserve = ft_strndup_gnl(reserve + tmp_reserve_len,
			ft_strlen_gnl(reserve) - tmp_reserve_len);
	ft_free_gnl((void **)&reserve);
	if (!tmp_reserve)
		return (NULL);
	return (tmp_reserve);
}

char	*get_next_line(int fd)
{
	char		*nl;
	char		*line;
	static char	*reserve;

	line = NULL;
	if (fd >= 0 && BUFFER_SIZE > 0)
	{
		if (!reserve || (reserve && !ft_strchr_gnl(reserve, '\n')))
			reserve = read_file_and_fill_reserve(fd, reserve);
		if (!reserve)
			return (line);
		nl = ft_strchr_gnl(reserve, '\n');
		line = ft_strndup_gnl(reserve, (nl - reserve) + 1);
		if (!line)
			return ((char *)ft_free_gnl((void **)&reserve));
		reserve = remove_extracted_line(reserve, nl);
	}
	return (line);
}
