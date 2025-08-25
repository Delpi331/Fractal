NAME = fractol
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iminilibx
LDFLAGS = -Lminilibx -lmlx -lX11 -lXext -lm
SRCS = utils.c Main.c fractal.c window.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re