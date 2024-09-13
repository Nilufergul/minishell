#include "../minishell.h"
int g_signal_status = 0;

void heredoc_signal(int sig)
{
	if (sig == SIGINT)
		g_signal_status |= (1 << 0);
}

void ctrl_d(char *line)
{
	if (!line)
	{
		ft_putstr_fd("exit\n", 1);
		free(line);
		exit(0);
	}
}

void ctrl_backs(int sig)
{
	(void)sig;
	g_signal_status |= (1 << 1);
	if (sig == SIGQUIT)
	{
		if (rl_line_buffer && *rl_line_buffer)
		{
			ft_putstr_fd("Quit : 3\n", 2);
			printf("%d\n", 131);
			if (g_signal_status & (1 << 2))
				exit(131);
		}
	}
}

void ctrl_c(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	write(1, "\033[A", 3);
	g_signal_status |= (1 << 3);
}

void signal_control(void)
{
	g_signal_status |= (1 << 2);
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_backs);
}
