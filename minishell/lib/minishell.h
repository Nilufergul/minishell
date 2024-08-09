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
# include "libft/libft.h"

typedef struct	s_mini
{
	char **env;
	char **arg;
}				t_mini;

typedef struct  s_cm
{
	char *cmd;
	char *arg;
	char *file;
	
}				t_cm;

void	get_env(t_mini *built);
int		env_size(char **environ);
void    ft_env(t_mini *built);
#endif