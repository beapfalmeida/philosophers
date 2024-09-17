CC = cc
CFLAGS = -Wextra -Wall -Werror -g
NAME = philo
SRC = philo.c simulation.c utils.c init.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
