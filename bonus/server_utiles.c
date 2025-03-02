/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenalla <fbenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:07:06 by fbenalla          #+#    #+#             */
/*   Updated: 2025/03/02 14:30:31 by fbenalla         ###   ########.fr       */
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

void	pid_check(pid_t process_id)
{
	if (kill(process_id, SIGUSR1) == -1)
	{
		write(2, "Process ID not found.\n", 23);
		exit(1);
	}
}

int	ft_which_byte(unsigned char buffer)
{
	int	byte;

	byte = 0;
	if ((buffer & 128) == 0)
		byte = 1;
	else if ((buffer & 224) == 192)
		byte = 2;
	else if ((buffer & 240) == 224)
		byte = 3;
	else if ((buffer & 248) == 240)
		byte = 4;
	return (byte);
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
