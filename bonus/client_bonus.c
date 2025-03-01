/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenalla <fbenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:57:44 by fbenalla          #+#    #+#             */
/*   Updated: 2025/03/01 12:45:52 by fbenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int	ft_atoi(char *str)
{
	int	nbr;
	int	i;
	int	signe;

	nbr = 0;
	i = 0;
	signe = 1;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - 48);
		i++;
	}
	return (nbr * signe);
}

void	send_char(pid_t pid_server, unsigned char octet)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((octet >> i) & 1)
			kill(pid_server, SIGUSR2);
		else
			kill(pid_server, SIGUSR1);
		usleep(250);
		usleep(250);
		i--;
	}
}

void	ack_handler(int recu, siginfo_t *info, void *context)
{
	(void)(info);
	(void)(context);
	if (recu == SIGUSR1)
	{
		write(1, "message recu\n", 14);
		exit(0);
	}
}

void	check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			write(2, "error in pid\n", 14);
			exit(1);
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	recieve;
	pid_t				process_id;
	char				*message;

	if (ac != 3)
	{
		write(2, "Usage ./client + PID + 'message' \n", 35);
		return (1);
	}
	check_digit(av[1]);
	process_id = ft_atoi(av[1]);
	recieve.sa_sigaction = ack_handler;
	sigaction(SIGUSR1, &recieve, NULL);
	message = av[2];
	while (*message)
	{
		send_char(process_id, *message);
		message++;
	}
	send_char(process_id, '\0');
	return (0);
}
