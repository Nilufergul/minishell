#include "../minishell.h"
int	g_exit_code = 0;

long long int	ft_longlong(const char *str)
{
	int			i;
	int			neg;
	long long	res;

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

static int	check_argument(const char *arg)
{
	int	j;

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

static int	valid_value(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if (arg[0] == '-')
	{
		if (len > ft_strlen("-9223372036854775808"))
			return (0);
		if (len == ft_strlen("-9223372036854775808")
			&& ft_strcmp(arg, "-9223372036854775808") > 0)
			return (0);
	}
	else
	{
		if (len > ft_strlen("9223372036854775807"))
			return (0);
		if (len == ft_strlen("9223372036854775807")
			&& ft_strcmp(arg, "9223372036854775807") > 0)
			return (0);
	}
	return (1);
}

static void	exit_handling(char **args, int i)
{
	long long	exit_code;

	if (!check_argument(args[0]) || !valid_value(args[0]))
	{
		printf("minishell: exit: %s: numeric argument required\n", args[0]);
		g_exit_code = 255;
		exit(g_exit_code);
	}
	exit_code = ft_longlong(args[0]);
	if (i == 1)
	{
		g_exit_code = exit_code % 256;
		exit(g_exit_code);
	}
	printf("minishell: exit: too many arguments\n");
}

void	ft_exit(char **args)
{
	int	i;

	i = 0;
	while (args && args[i] != NULL)
		i++;
	printf("exit\n");
	if (!args)
		exit(g_exit_code);
	exit_handling(args, i);
}
