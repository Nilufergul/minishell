NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror 
M_SRC = minishell.c \
		parser/dolarsign.c parser/parser.c parser/adding_space.c parser/split.c parser/syntax.c \
		execute/echo_helper.c execute/echo_main.c execute/exit.c execute/pwd.c \
		utils/struct_utils.c utils/syntax_utils.c \
		syntax/check_the_syntax.c syntax/pipe_check.c syntax/print_utils.c syntax/redir_check.c 
LIB_SRC = 
SRC = $(M_SRC) $(LIB_SRC)
OBJ = $(SRC:.c=.o)
READLINE = -L./lib/readline/lib -I./lib/readline/include/readline -lreadline 
DIR     = $(shell echo $(PWD))
RM = rm -rf
RL = ./lib/readline/lib/libreadline.a
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(RL) $(LIBFT) $(OBJ)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(READLINE) 

$(LIBFT):
	@${MAKE} -C libft

$(RL):
		@echo "Downloading readline"
		@curl -O https://ftp.gnu.org/gnu/readline/readline-8.2-rc1.tar.gz
		@tar -xvf readline-8.2-rc1.tar.gz
		@$(RM) readline-8.2-rc1.tar.gz
		@cd readline-8.2-rc1 && ./configure --prefix=$(DIR)/lib/readline && make && make install
		@$(RM) readline-8.2-rc1
		@ echo "Readline installed"

RLclean:
		@$(RM) lib/readline
		@$(RM) lib
		@echo "Readline removed"


clean:
		$(RM) $(OBJ)
		@make -C libft clean

fclean: clean
		$(RM) $(NAME)
		@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re push
