/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenalla <fbenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 03:33:23 by fbenalla          #+#    #+#             */
/*   Updated: 2025/02/23 17:05:49 by fbenalla         ###   ########.fr       */
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

void	handler(int signal, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int				client_pid = 0;
	static int				bit = 0;

	(void)(context);
	if (client_pid != info->si_pid)
	{
		client_pid = info->si_pid;
		c = 0;
		bit = 0;
	}
	if (signal == SIGUSR2)
		c = (c << 1) | 1;
	else if (signal == SIGUSR1)
		c = (c << 1);
	bit++;
	if (bit == 8)
	{
		if (c == '\0')
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		bit = 0;
		c = 0;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	pid_t				pid;

	(void)(av);
	if (ac > 1)
	{
		write(2, "Usage : ./server \n", 19);
		return (1);
	}
	pid = getpid();
	write(0, "The Process PID is : ", 22);
	ft_putnbr(pid);
	write(0, "\n", 1);
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
