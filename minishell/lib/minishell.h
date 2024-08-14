#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <term.h>
# include <curses.h>
//# include "libft/libft.h"

# define EXEC 0
# define HEREDOC 1
# define PIPE 2
# define GREAT 3
# define GREATER 4
# define LESS 5
# define STDINN 0
# define STDOUT 1
# define STDERR 2

typedef struct	s_mini
{
	char **env;
	char **line;
}				t_mini;

typedef struct s_fd
{
	int *fd;
	struct t_fd *next;
}			t_fd;

typedef struct s_ty
{
	int *type;
	struct t_ty *next;
}				t_ty;

typedef struct s_arg
{
	char *arg;
	struct t_arg *next;
}				t_arg;

typedef struct  s_line
{
	char	*cmd;
	struct	**arg;
	struct  t_ty    *type;
	struct  t_fd    *fd;
	char	*flag;
    struct  t_mini  *minis;	
	struct  t_line  *next;
}				t_line;

void    get_env(t_mini *built ,char** environ);
int		env_size(char **environ);
void    ft_env(t_mini *built);
int quote_checker_1(t_mini *mini);

#endif
