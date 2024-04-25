NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address 
CFILES = helper.c helper1.c main.c
OFILSE = $(CFILES:.c=.o)


all: $(NAME)


$(NAME): $(OFILSE)
	$(CC) $(CFLAGS) $(OFILSE) -o $(NAME)

clean:
	rm -f $(OFILSE)

fclean: clean
	rm -f $(NAME)

re: fclean all