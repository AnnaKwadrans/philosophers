CC = cc
FLAGS = -Wall -Wextra -Werror -pthread
NAME = philo
RM = rm -f

SRC = main.c validator.c utils.c data.c time.c forks.c philos.c watch.c routine.c aux.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

.PHONY:	all clean fclean re

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	clean all
