NAME		= pipex


SRCS		= pipex.c temp_main.c struct_utils.c echo_helper.c echo_main.c cd.c \
			 export.c unset.c exit.c env.c heredoc.c pipex2.c pipex3.c struct_utils2.c \
			 go_exe.c


LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -I$(LIBFT_DIR) -g -lreadline -fsanitize=address

$(NAME): $(LIBFT) $(SRCS)
	@$(CC) $(CFLAGS) $(SRCS) -L$(LIBFT_DIR) -lft -o $(NAME)

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

all: $(NAME) $(BONUS)

bonus: $(BONUS)

$(BONUS): $(LIBFT) $(BONUS_SRCS)
	@$(CC) $(CFLAGS) $(BONUS_SRCS) -L$(LIBFT_DIR) -lft -o $(BONUS)

clean:
	@make -s -C $(LIBFT_DIR) clean

fclean: clean
	@make -s -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
