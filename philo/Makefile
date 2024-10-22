# Project settings
NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror
INCLUDE = -I include

SRCS =	src/philosophers.c	\
		src/fork.c			\
		src/input_handler.c	\
		src/utils.c			\
		src/states.c		\
		src/time.c			\
		src/main.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(FLAGS) $(SRCS) $(INCLUDE) -o $(NAME)

clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re