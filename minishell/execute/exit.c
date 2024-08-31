#include "builtins.h"

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
		write(2, "minishell: exit: numeric argument required\n", 43);
		exit(255);
	}
	exit_code = ft_atoi(args[1]);
	if (i == 2)
		exit(exit_code);
	write(2, "minishell: exit: too many arguments\n", 36);
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
