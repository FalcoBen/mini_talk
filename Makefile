# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbenalla <fbenalla@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/01 12:43:25 by fbenalla          #+#    #+#              #
#    Updated: 2025/03/02 16:33:40 by fbenalla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = client server
NAME_BONUS = client_bonus server_bonus

HEADER = include/minitalk.h
HEADER_BONUS = include/minitalk_bonus.h

RM = rm -f

SRCF = mandatory/client.c mandatory/server.c bonus/server_utiles.c

SRCF_BONUS = bonus/client_bonus.c bonus/server_bonus.c bonus/server_utiles.c

OBJC = $(SRCF:.c=.o)

OBJC_BONUS = $(SRCF_BONUS:.c=.o)

all: $(NAME)

bonus: $(NAME_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJC) $(HEADER)
	$(CC) $(CFLAGS) -o mandatory/client mandatory/client.o
	mv mandatory/client .
	$(CC) $(CFLAGS) -o mandatory/server mandatory/server.o 
	mv mandatory/server .
	
$(NAME_BONUS): $(OBJC_BONUS) $(HEADER_BONUS)
	$(CC) $(CFLAGS) -o bonus/client_bonus bonus/client_bonus.o bonus/server_utiles.o
	mv bonus/client_bonus .
	$(CC) $(CFLAGS) -o bonus/server_bonus bonus/server_bonus.o bonus/server_utiles.o
	mv bonus/server_bonus .

clean:
	$(RM) $(OBJC) $(OBJC_BONUS)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all