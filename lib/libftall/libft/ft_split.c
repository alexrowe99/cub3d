/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:32:55 by lmells            #+#    #+#             */
/*   Updated: 2023/08/13 15:09:47 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftall.h"
#include <stdlib.h>

static size_t	get_word_count(const char *s, char c, size_t s_len)
{
	size_t	i;
	size_t	wc;

	i = 0;
	wc = 0;
	while (++i <= s_len)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			wc++;
		s++;
	}
	return (wc);
}

static char	*extract_word(char **s, char c)
{
	char	*w;
	char	*sp;
	size_t	i;

	while (**s == c)
		(*s)++;
	sp = *s;
	while (*sp != c && *sp != '\0')
		sp++;
	w = malloc((sp - *s) + 1);
	if (!w)
		return (NULL);
	i = 0;
	while ((*s)[i] != c && (*s)[i] != '\0')
	{
		w[i] = (*s)[i];
		i++;
	}
	w[i] = '\0';
	*s = sp;
	return (w);
}

char	**ft_split(const char *s, char c)
{
	size_t	i;
	size_t	wc;
	char	**split;

	wc = get_word_count(s, c, ft_strlen(s));
	split = ft_calloc(wc + 1, sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	while (i < wc)
	{
		split[i] = extract_word((char **)&s, c);
		if (!split[i])
			break ;
		i++;
	}
	if (i < wc)
	{
		while (i--)
			free(split[i]);
		free(split);
		return (NULL);
	}
	return (split);
}
