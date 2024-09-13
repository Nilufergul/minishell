#include "../minishell.h"

int	heredoc(char *target)
{
	int		pipefd[2];
	char	*input;

	input = 0;
	init_signals_heredoc();
	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	while (1)
	{
		input = readline("> ");
		if (g_catch_ctrlc == 1)
			break ;
		if (heredoc_ctrld(input))
			break ;
		if (!input)
			exit(EXIT_FAILURE);
		if (ft_strcmp(input, target) == 0)
		{
			free(input);
			break ;
		}
		if (write(pipefd[1], input, ft_strlen(input)) == -1)
			exit(EXIT_FAILURE);
		if (write(pipefd[1], "\n", 1) == -1)
			exit(EXIT_FAILURE);
		free(input);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}
