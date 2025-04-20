CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
SRC = shell.c
OBJ = $(SRC:.c=.o)
NAME = shell

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

