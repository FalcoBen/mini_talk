/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenalla <fbenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:57:40 by fbenalla          #+#    #+#             */
/*   Updated: 2025/03/02 16:30:09 by fbenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk_bonus.h"

void	do_(t_t *set, unsigned char *buffer)
{
	if (set->bit == 8)
	{
		set->bit = 0;
		if (set->byte_index == 0)
			set->expected_bytes = ft_which_byte(buffer);
		(set->byte_index)++;
		if (set->byte_index == set->expected_bytes)
		{
			if (buffer[set->bit] == '\0')
			{
				write(1, "\n", 1);
				kill(set->client_pid, SIGUSR1);
			}
			write(1, buffer, set->expected_bytes);
			set->byte_index = 0;
			ft_memset(buffer, 0, 4);
		}
		if (buffer[set->byte_index - 1] == '\0')
		{
			set->byte_index = 0;
			ft_memset(buffer, 0, 4);
		}
		else
			return ;
	}
}

void	check_pid(t_t *set, int *si_pid, unsigned char *buffer)
{
	if (set->client_pid != *si_pid)
	{
		set->client_pid = *si_pid;
		set->bit = 0;
		set->byte_index = 0;
		set->expected_bytes = 1;
		ft_memset(buffer, 0, 4);
	}
}

void	handler(int signal, siginfo_t *info, void *context)
{
	static unsigned char	buffer[4];
	static t_t				set = {0};

	(void)(context);
	check_pid(&set, &info->si_pid, buffer);
	if (signal == SIGUSR2 && set.first)
	{
		set.first = false;
		return ;
	}
	if (signal == SIGUSR2)
		buffer[set.byte_index] = (buffer[set.byte_index] << 1) | 1;
	else if (signal == SIGUSR1)
		buffer[set.byte_index] = (buffer[set.byte_index] << 1);
	set.bit++;
	do_(&set, buffer);
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
	write(1, "The Process PID is : ", 22);
	ft_putnbr(pid);
	write(1, "\n", 1);
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
