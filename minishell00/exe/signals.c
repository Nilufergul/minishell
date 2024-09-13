#include "../minishell.h"

static void	ctrl_c(int signum)
{
	if (signum == CTRL_C)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	handle_child(int signum)
{
	if (signum == CTRL_C)
		printf("\n");
}

int	init_signals(int mode)
{
	if (mode == 0)
		signal(CTRL_C, ctrl_c);
	else if (mode == 1)
		signal(CTRL_C, handle_child);
	signal(CTRL_SLASH, ctrl_c);
	return (1);
}

void	ctrl_d(char *line)
{
	if (!line)
	{
		ft_putstr_fd("exit\n", 1);
		free(line);
		exit(0);
	}
}
