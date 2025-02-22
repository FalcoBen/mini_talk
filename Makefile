CC = cc 
CFLAGS = -Wall -Wextra -Werror
NAME = mandatory/client mandatory/server
NAME_BONUS = bonus/client_bonus bonus/server_bonus

HEADER = include/minitalk.h

RM = rm -f

SRCF = mandatory/client.c mandatory/server.c
SRCF_BONUS =  bonus/client_bonus.c bonus/server_bonus.c

OBJC = $(SRCF:.c=.o)
OBJC_BONUS = $(SRCF_BONUS:.c=.o)

all : $(NAME)

bonus : $(NAME_BONUS)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJC) $(OBJC_BONUS)
fclean : clean
	$(RM) $(NAME) $(NAME_BONUS)

re : fclean all
