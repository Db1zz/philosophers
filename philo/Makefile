# Project settings
NAME = philo
CC = cc
FLAGS = -Wall -Wextra #-Werror

SRCS =	philosophers.c	\
		fork.c			\
		input_handler.c	\
		utils.c			\
		states.c		\
		time.c			\
		main.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re