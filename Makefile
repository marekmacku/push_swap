NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c \
	chunking.c \
	ft_split.c \
	isDigit.c \
	normalize.c \
	rev_rotate_ops.c \
	rotate_ops.c \
	parser.c \
	sort_utils.c \
	find_best_in_chunk.c \
	common_rotations.c \
	update_move_utils.c \
	find_cheapest_move.c \
	push_ops.c \
	swap_ops.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

