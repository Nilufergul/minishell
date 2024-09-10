#include "../minishell.h"
int global_exit_code = 0;

long long int ft_longlong(const char *str)
{
	int i;
	int neg;
	int res;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			neg *= -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	return (res * neg);
}

static int check_argument(const char *arg)
{
	int j;

	j = 0;
	if (arg[j] == '+' || arg[j] == '-')
		j++; // Skip the initial + or - sign
	while (arg[j])
	{
		if (arg[j] < '0' || arg[j] > '9')
			return (0);
		j++;
	}
	return (1);
}

static int valid_value(char *arg)
{
	char *longmax = "9223372036854775807";
	char *longmin = "-9223372036854775808";
	size_t len = strlen(arg);

	if (arg[0] == '-')
	{
		if (len > ft_strlen(longmin))
			return 0;
		if (len == ft_strlen(longmin) && ft_strcmp(arg, longmin) > 0)
			return 0;
	}
	else
	{
		if (len > ft_strlen(longmax))
			return 0;
		if (len == ft_strlen(longmax) && strcmp(arg, longmax) > 0)
			return 0;
	}
	return 1;
}

static void exit_handling(char **args, int i)
{
	long long exit_code;

	if (!check_argument(args[0]) || !valid_value(args[0]))
	{
		printf("minishell: exit: %s: numeric argument required\n", args[0]);
		global_exit_code = 255;
		exit(global_exit_code);
	}

	exit_code = ft_longlong(args[0]);
	if (i == 1)
	{
		global_exit_code = exit_code % 256;
		exit(global_exit_code);
	}
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
		exit(global_exit_code);
	exit_handling(args, i);
}
