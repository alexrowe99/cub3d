/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arowe <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:58:43 by arowe             #+#    #+#             */
/*   Updated: 2021/10/08 12:58:43 by arowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	ft_strrev(char *tab, int size)
{
	int		counter;
	int		rev_counter;
	char	temp;

	counter = 0;
	rev_counter = size - 1;
	while (counter != rev_counter && counter < rev_counter)
	{
		temp = tab[counter];
		tab[counter] = tab[rev_counter];
		tab[rev_counter] = temp;
		counter++;
		rev_counter--;
	}
	tab[size] = '\0';
}

static int	ft_numdigits(int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*dest;
	int				i;
	int				offset;
	unsigned int	x;

	offset = 0;
	if (n < 0)
		offset = 1;
	dest = (char *)malloc(sizeof(char) * (ft_numdigits(n) + offset));
	if (!dest)
		return (NULL);
	x = n;
	if (n < 0)
		x = -n;
	i = 0;
	while (x > 0 || (i == 0 && x == 0))
	{
		dest[i++] = (x % 10) + '0';
		x /= 10;
	}
	if (offset == 1)
		dest[i] = '-';
	ft_strrev(dest, i + offset);
	return (dest);
}
