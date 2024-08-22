NAME = minishell
SRC = minishell.c \
      parser/dolarsign.c parser/parser.c parser/parser2.c parser/split.c parser/syntax.c \
      execute/echo_helper.c execute/echo_main.c execute/exit.c execute/pwd.c \
      utils/struct_utils.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
CC = gcc
RM = rm -rf
LIBFT = libft/libft.a
READLINE = readline
OBJ = $(SRC:.c=.o)

all: $(READLINE) $(LIBFT) $(NAME)

$(READLINE):
	@clear
	@curl -s -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz 2>&1
	@tar -xvf readline-8.2.tar.gz 2>&1 | awk '{printf "♣"; fflush()}' 2>&1
	@cd readline-8.2 && ./configure --prefix=${PWD}/readline 2>&1 | awk '{printf "♣"; fflush()}' 2>&1
	@cd readline-8.2 && make install 2>&1 | awk '{printf "♣"; fflush()}' 2>&1
	@rm -rf readline
	@echo "$(RESET)"
	

$(LIBFT):
	@make -C libft | awk '{printf "♣"; fflush()}'
	@${MAKE} -C libft
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${PWD}/readline/include/

$(NAME): $(SRC) $(OBJ)
	@$(CC) $(CFLAGS) $(LIBFT) $(SRC) -L${PWD}/readline/lib -I${PWD}/readline/include/ -lreadline -o $(NAME) 2>&1
	@clear
	@echo "Minishell Compiled"
	@echo "$(RESET)"

clean:
	@clear
	@$(RM) $(OBJ)
	@make -C libft clean

fclean: clean
	@$(RM) $(NAME)
	@make -C libft fclean
	@rm -rf readline
	@rm -rf readline-8.2 readline-8.2.tar.gz
	@clear

re: fclean all

.PHONY: all clean fclean re
