CC = cc 
# CFLAGS = -Wall -Wextra -Werror
SRCF = client.c server.c
NAME = client server
HEADER = minitalk.h
RM = rm -f

OBJC = $(SRCF:.c=.o)

all : $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@


clean :
	$(RM) $(OBJC)
fclean : clean
	$(RM) $(NAME)

re : fclean all
