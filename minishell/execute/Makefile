CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = ../libft/libft.a

SRCS = builtin_tests.c export.c unset.c exit.c cd.c echo_helper.c env.c pwd.c
OBJS = $(SRCS:.c=.o)
NAME = minishell

all: libft $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

libft:
	$(MAKE) -C ../libft

clean:
	rm -f $(OBJS)
	$(MAKE) -C ../libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ../libft fclean

re: fclean all
