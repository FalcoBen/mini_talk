/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenalla <fbenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:25:49 by fbenalla          #+#    #+#             */
/*   Updated: 2025/03/02 16:35:38 by fbenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_t
{
	int				bit;
	int				byte_index;
	int				client_pid;
	int				expected_bytes;
	bool			first;
}	t_t;

int		ft_which_byte(unsigned char buffer[4]);
void	ft_putnbr(int nbr);
void	*ft_memset(void *b, int c, size_t len);
void	pid_check(pid_t process_id);

#endif