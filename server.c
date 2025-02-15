/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenalla <fbenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 03:33:23 by fbenalla          #+#    #+#             */
/*   Updated: 2025/02/15 04:33:56 by fbenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minitalk.h"

void ft_putnbr(int nbr)
{
	if(nbr > 9)
		ft_putnbr(nbr/10);
	char c = (nbr % 10) + '0';
	write(1, &c, 1);
}

void handler(int signal)
{
    // static unsigned char c = 0;
    // static int bit = 0;

    if (signal == SIGUSR2)
	{
        // c = (c << 1) | 1; // Store bit as 1
		write(1, "1", 1);
	}
    else if (signal == SIGUSR1)
	{	
		write(1, "0", 1);
        // c = (c << 1); // Store bit as 0
	}
    // bit++;

    // if (bit == 8) // When 8 bits received, print char
    // {
    //     write(1, &c, 1);
    //     bit = 0;
    //     c = 0;
    // }
}


// void handler(int signal)
// {
// 	// int i = 7;
	
// 	if(signal == SIGUSR2)
// 	{
// 		write(1, "1", 1);
// 	}
// 	else if(signal == SIGUSR1)
// 		write(1, "0", 1);
// 	sleep (1);
// }

int main(int ac, char **av)
{
	if(ac > 1)
	{
		printf("Usage ./server \n");
		return 0;
	}
	pid_t pid = getpid();
	write(1, "The Process PID is ", 20);
	ft_putnbr(pid);
	write(1, "\n", 1);
	struct sigaction sa;
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	// sigaction(SIGINT, &sa, NULL);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	write(1, "\n", 1);
	while(1)
		pause();
	return 0;
}