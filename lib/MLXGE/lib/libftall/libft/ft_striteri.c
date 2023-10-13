/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:25:32 by lmells            #+#    #+#             */
/*   Updated: 2023/07/12 15:31:28 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(const char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, (char *)&s[i]);
		i++;
	}
}