/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenalla <fbenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 21:25:41 by fbenalla          #+#    #+#             */
/*   Updated: 2025/02/28 23:51:22 by fbenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_t
{
	int				bit;
	int				byte_index;
	int				client_pid;
	int				expected_bytes;
}	t_t;

int		ft_which_byte(unsigned char buffer[4]);
void	ft_putnbr(int nbr);
void	*ft_memset(void *b, int c, size_t len);
void	do_(t_t *set, unsigned char *buffer);
void	check_pid(t_t *set, int *si_pid, unsigned char *buffer);
void	handler(int signal, siginfo_t *info, void *context);
