/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenalla <fbenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 23:37:58 by fbenalla          #+#    #+#             */
/*   Updated: 2025/02/28 23:50:50 by fbenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	ft_putnbr(int nbr)
{
	char	c;

	if (nbr > 9)
		ft_putnbr(nbr / 10);
	c = (nbr % 10 + '0');
	write(1, &c, 1);
}

int	ft_which_byte(unsigned char buffer[4])
{
	int	expected_bytes;

	expected_bytes = 0;
	if ((buffer[0] & 128) == 0)
		expected_bytes = 1;
	else if ((buffer[0] & 224) == 192)
		expected_bytes = 2;
	else if ((buffer[0] & 240) == 224)
		expected_bytes = 3;
	else if ((buffer[0] & 248) == 240)
		expected_bytes = 4;
	return (expected_bytes);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)b;
	i = 0;
	if (len == 0)
		return (b);
	while (i < len)
	{
		str[i] = c;
		i++;
	}
	return (b);
}
