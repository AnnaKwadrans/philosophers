CC = cc
FLAGS = -Wall -Wextra -Werror -pthread
NAME = philo
RM = rm -f

SRC = main.c validator.c data.c philos.c routine.c utils.c

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
