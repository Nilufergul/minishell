NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
M_SRC = minishell.c \
	parser/insert_space.c parser/split.c parser/space_utils.c\
	parser/ready_for_exe.c parser/removing_quotes.c utils/struct_utils.c utils/struct_utils2.c \
	utils/syntax_utils.c syntax/checking_syntax.c utils/free_split.c \
	syntax/pipe_check.c syntax/print_utils.c syntax/redir_check.c \
	parser/split_utils.c parser/split_utils2.c exe/pipex.c exe/signals.c exe/signals_heredoc.c\
	exe/echo.c exe/cd.c exe/export.c exe/export_utils.c exe/unset.c \
	exe/env.c exe/pwd.c exe/heredoc.c exe/pipex2.c exe/pipex3.c exe/pipex4.c\
	exe/go_exe.c exe/exit.c exe/make_pipe.c utils/get_free.c parser/dollar_utils2.c parser/dollar_utils1.c
LIB_SRC =
SRC = $(M_SRC) $(LIB_SRC)
OBJ = $(SRC:.c=.o)
READLINE = -L$(DIR)/lib/readline/lib -I$(DIR)/lib/readline/include/readline -lreadline
DIR = $(shell echo $(PWD))
RM = rm -rf
RL = $(DIR)/lib/readline/lib/libreadline.a
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(RL) $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(READLINE)

$(LIBFT):
	@$(MAKE) -C libft

$(RL):
	@echo "Downloading readline"
	@if [ ! -d "$(DIR)/lib/readline/lib" ]; then \
		mkdir -p $(DIR)/lib/readline/lib; \
		curl -O https://ftp.gnu.org/gnu/readline/readline-8.2-rc1.tar.gz; \
		tar -xvf readline-8.2-rc1.tar.gz; \
		$(RM) readline-8.2-rc1.tar.gz; \
		cd readline-8.2-rc1 && ./configure --prefix=$(DIR)/lib/readline && make && make install; \
		$(RM) readline-8.2-rc1; \
		echo "Readline installed"; \
	fi

RLclean:
	$(RM) $(DIR)/lib/readline
	@rm -rf lib
	@rm -rf readline-8.2-rc1
	@echo "Readline removed"

clean:
	$(RM) $(OBJ)
	@$(MAKE) -C libft clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re push
