#include "../minishell.h"

int heredoc(char *target)
{
    int pipefd[2];
    char *input;

    signal(SIGINT, heredoc_signal);

    input = 0;
    if (pipe(pipefd) == -1)
        exit(EXIT_FAILURE);

    while (1)
    {
        input = readline("> ");
        if (!input)
        {
            if (g_signal_status & (1 << 0))
            {
                free(input);
                close(pipefd[1]);
                return (pipefd[0]);
            }
            else
            {
                free(input);
                close(pipefd[1]);
                return (pipefd[0]);
            }
        }

        if (ft_strcmp(input, target) == 0)
        {
            free(input);
            break;
        }

        if (write(pipefd[1], input, ft_strlen(input)) == -1 ||
            write(pipefd[1], "\n", 1) == -1)
        {
            free(input);
            exit(EXIT_FAILURE);
        }
        free(input);
    }
    close(pipefd[1]);
    return (pipefd[0]);
}