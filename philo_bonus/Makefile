# Project settings
NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I include

SRCS =	src/main.c	\
		src/fork.c	\
		src/philosophers.c	\
		src/routine.c		\
		src/semaphore.c		\
		src/states.c		\
		src/input_parcer.c	\
		src/time.c			\
		src/utils.c			\

SRC_DIR = src

OBJS = $(SRCS:src/%.c=objs/%.o)
OBJS_DIR = objs

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(INCLUDE) -o $(NAME)

clean:
	rm -f $(OBJS)
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
