#include "../minishell.h"

long long int ft_longlong(const char *str)
{
	int i;
	int neg;
	long long res;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
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
		j++;
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
	size_t len;

	len = ft_strlen(arg);
	if (arg[0] == '-')
	{
		if (len > ft_strlen("-9223372036854775808"))
			return (0);
		if (len == ft_strlen("-9223372036854775808") && ft_strcmp(arg, "-9223372036854775808") > 0)
			return (0);
	}
	else
	{
		if (len > ft_strlen("9223372036854775807"))
			return (0);
		if (len == ft_strlen("9223372036854775807") && ft_strcmp(arg, "9223372036854775807") > 0)
			return (0);
	}
	return (1);
}

static void exit_handling(char **args, int i, int *exit_code)
{
	long long int exit_but_looong;
	if (!check_argument(args[0]) || !valid_value(args[0]))
	{
		printf("minishell: exit: %s: numeric argument required\n", args[0]);
		*exit_code = 255;
		exit(*exit_code);
	}
	exit_but_looong = ft_longlong(args[0]);
	if (i == 1)
	{
		*exit_code = exit_but_looong % 256;
		exit(*exit_code);
	}
	printf("minishell: exit: too many arguments\n");
}

void ft_exit(t_line *line)
{
	int i;

	i = 0;
	while (line->arg && line->arg[i] != NULL)
		i++;
	printf("exit\n");
	if (!line->arg)
	{
		*line->exit_code_line = 0;
		exit(0);
	}
	exit_handling(line->arg, i, line->exit_code_line);
}
