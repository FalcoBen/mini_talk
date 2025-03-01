# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbenalla <fbenalla@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/01 12:43:25 by fbenalla          #+#    #+#              #
#    Updated: 2025/03/01 12:43:28 by fbenalla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = mandatory/client mandatory/server
NAME_BONUS = bonus/client_bonus bonus/server_bonus

HEADER = include/minitalk.h

RM = rm -f

SRCF = mandatory/client.c mandatory/server.c

SRCF_BONUS = bonus/client_bonus.c bonus/server_bonus.c bonus/server_utiles.c

OBJC = $(SRCF:.c=.o)

OBJC_BONUS = $(SRCF_BONUS:.c=.o)

all: $(NAME)

bonus: $(NAME_BONUS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME_BONUS): $(OBJC_BONUS)
	$(CC) $(CFLAGS) -o bonus/client_bonus bonus/client_bonus.o
	$(CC) $(CFLAGS) -o bonus/server_bonus bonus/server_bonus.o bonus/server_utiles.o

clean:
	$(RM) $(OBJC) $(OBJC_BONUS)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all