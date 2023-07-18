/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 13:43:34 by lmells            #+#    #+#             */
/*   Updated: 2023/07/18 15:35:01 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

// Prototype
char	*get_next_line(int fd);

// Utils
void	*ft_free_gnl(void **heap);
char	*ft_strchr_gnl(const char *s, int c);
char	*ft_strndup_gnl(const char *s, size_t n);
void	*ft_calloc_gnl(size_t nmemb, size_t size);
size_t	ft_strlen_gnl(const char *s);

#endif
