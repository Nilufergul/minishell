
// exit [n] seklinde calısacakmıs

//shell ismi sonradan degisirse bu fonksiyon güncellenecek. exitin önüne shell ismi gelecek

#include "../minishell.h"
#include <unistd.h>
#include <stdlib.h>

static int	check_argument(char *arg)
{
	int	j;

	j = 0;
	while (arg[j])
	{
		if (arg[j] != '-' && (arg[j] < '0' || arg[j] > '9'))
			return (0);
		j++;
	}
	return (1);
}

static void	exit_handling(char **args, int i)
{
	int	exit_code;

	if (i == 1)
		exit(0);
	if (!check_argument(args[1]))
	{
		write(2, "exit: numeric argument required\n", 33);
		exit(255);
	}
	exit_code = atoi(args[1]);
	if (i == 2)
		exit(exit_code);
	write(2, "exit: too many arguments\n", 25);
}

void	ft_exit(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
		i++;
	write(1, "exit\n", 5);
	exit_handling(args, i);
}


/*
#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	ft_exit(char **args);

int	main(void)
{
	char	*line;
	char	**args;
	int		arg_count;
	int		i;

	while (1)
	{
		printf("minishell> ");
		line = NULL;
		size_t len = 0;
		getline(&line, &len, stdin);

		line[strcspn(line, "\n")] = '\0';

		arg_count = 0;
		args = malloc(sizeof(char *) * 10);
		char *token = strtok(line, " ");
		while (token != NULL)
		{
			args[arg_count++] = strdup(token);
			token = strtok(NULL, " ");
		}
		args[arg_count] = NULL;

		if (arg_count > 0 && strcmp(args[0], "exit") == 0)
			ft_exit(args);

		for (i = 0; i < arg_count; i++)
			free(args[i]);
		free(args);
		free(line);
	}
	return (0);
}
*/
/*
	test için
	"-10"
	"randomword"
	"random" "word"
	"-10192" "random"
	"-43" "-124"
*/
