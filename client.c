/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenalla <fbenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 03:33:25 by fbenalla          #+#    #+#             */
/*   Updated: 2025/02/15 04:29:04 by fbenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minitalk.h"


int ft_atoi(char *str)
{
    int nbr = 0;
    int i = 0;
    int signe = 1;
    while(str[i] == ' ' || str[i] == '\t')
        i++;
    if(str[i] == '-' || str[i]  == '+')
    {
        if(str[i] == '-') 
            signe = -1;
        i++;
    }
    while(str[i] >= '0' && str[i] <= '9')
    {
        nbr = nbr * 10 + (str[i] - 48);
        i++;
    }
    return (nbr * signe);
} 

void send_char(pid_t pid_server, unsigned char octet)
{
    int i = 7;
    while(i >= 0)
    {
        if((octet >> i) & 1)
        {
            kill(pid_server, SIGUSR2);
            printf("send 1 \n"); // 1
        }
        else 
        {
            kill(pid_server, SIGUSR1);  // 0
            printf("send 0 \n"); // 1
        }
        usleep(100);
        i--;
    }
}
int main(int ac, char **av)
{
    if(ac != 3)
    {
        printf("Usage ./client + PID + 'message' \n");
        return 0;
    }
    pid_t process_id;
    process_id = ft_atoi(av[1]);
    char *message = av[2];
    while(*message)
    {
        send_char(process_id, *message);
        message++;
    }
    // send_char(process_id, '\0');
    return 0;
}

//A =  01000001