/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arowe <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:59:23 by arowe             #+#    #+#             */
/*   Updated: 2021/10/08 12:59:23 by arowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	index;
	int	res;
	int	temp;

	index = 0;
	res = 1;
	temp = 0;
	while (str[index] == ' ' || str[index] == '\n'
		|| str[index] == '\t' || str[index] == '\v'
		|| str[index] == '\f' || str[index] == '\r')
		index++;
	if (str[index] == '+' || str[index] == '-')
	{
		if (str[index] == '-')
			res *= -1;
		index++;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		temp *= 10;
		temp += (str[index] - '0');
		index++;
	}
	return (temp * res);
}
