/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arowe <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:58:44 by arowe             #+#    #+#             */
/*   Updated: 2021/10/08 12:58:44 by arowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static unsigned int	ft_abs_p(int n)
{
	if (n < 0)
	{
		return (-1 * n);
	}
	return (n);
}

int	num_to_str(int num, char *dest)
{
	unsigned int	nb_arr[10];
	unsigned int	temp;
	unsigned int	count;
	unsigned int	reverse_count;
	unsigned int	absolute_nb;

	if (num == 0)
	{
		*dest = '0';
		return (1);
	}
	absolute_nb = ft_abs_p(num);
	count = 0;
	while (absolute_nb > 0)
	{
		temp = absolute_nb % 10;
		absolute_nb = absolute_nb / 10;
		nb_arr[count++] = temp;
	}
	reverse_count = 0;
	while (count > 0)
		dest[--count] = nb_arr[reverse_count++] + '0';
	return (reverse_count);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	nb_str[10];

	if (n < 0)
	{
		write(fd, "-", 1);
	}
	write(fd, nb_str, num_to_str(n, nb_str));
}
