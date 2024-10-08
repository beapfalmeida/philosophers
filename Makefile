CC = cc
CFLAGS = -Wextra -Wall -Werror -g
NAME = philo
SRC = philo.c init.c simulation.c eating.c utils.c  get_and_set.c  
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
