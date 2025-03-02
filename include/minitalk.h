/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenalla <fbenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 21:25:41 by fbenalla          #+#    #+#             */
/*   Updated: 2025/03/02 14:30:40 by fbenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <libc.h>

typedef struct s_t
{
	int				bit;
	int				byte_index;
	int				client_pid;
	int				expected_bytes;
}	t_t;

int		ft_which_byte(unsigned char buffer);
void	ft_putnbr(int nbr);
void	*ft_memset(void *b, int c, size_t len);
void	pid_check(pid_t process_id);

#endif