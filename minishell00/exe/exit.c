#include "../minishell.h"

static int check_argument(char *arg)
{
	int j;

	j = 0;
	while (arg[j])
	{
		if (arg[j] == '-' && j == 0)
			j++;
		else if (arg[j] < '0' || arg[j] > '9')
			return (0);
		else
			j++;
	}
	return (1);
}

static int valid_value(char *arg)
{
	size_t len = strlen(arg);

	if (arg[0] != '-' && len == ft_strlen("2147483647"))
	{
		if (ft_strcmp(arg, "2147483647") > 0)
			return 0;
	}
	else if (len > ft_strlen("2147483647"))
	{
		return 0;
	}

	return 1;
}

static void exit_handling(char **args, int i)
{
	int exit_code;

	if (!check_argument(args[0]) || !valid_value(args[0]))
	{
		printf("minishell: exit: numeric argument required\n");
		exit(255);
	}

	exit_code = ft_atoi(args[0]);
	if (i == 1)
		exit(exit_code);
	printf("minishell: exit: too many arguments\n");
}

void ft_exit(char **args)
{
	int i;

	i = 0;

	while (args && args[i] != NULL)
		i++;
	printf("exit\n");
	if (!args)
		exit(0);
	exit_handling(args, i);
}
