#include "../minishell.h"

int is_valid(const char *str)
{
	int i;

	if (!str || *str == '\0' || *str == '=' || !ft_isalpha(*str))
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int print_export(char **env)
{
	int i;
	char *equal_sign;

	i = 0;
	while (env[i])
	{
		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			printf("declare -x %s=\"%s\"\n", env[i], equal_sign + 1);
			*equal_sign = '=';
		}
		else
			printf("declare -x %s\n", env[i]);
		i++;
	}
	return (0);
}

int handle_export_argument(t_line *line, const char *arg)
{
	char *equal_sign;

	if (arg[0] == '=')
	{
		printf("export: `%s': not a valid identifier\n", arg);
		return (1);
	}
	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		if (!is_valid(arg))
		{
			printf("export: `%s': not a valid identifier\n", arg);
			*equal_sign = '=';
			return (1);
		}
		if (*(equal_sign + 1) != '\0')
			create_update(line->env, arg, equal_sign + 1);
		else
			create_update(line->env, arg, "");
		*equal_sign = '=';
	}
	else if (!is_valid(arg))
	{
		printf("export: `%s': not a valid identifier\n", arg);
		return (1);
	}
	return (0);
}

int ft_export(t_line *line)
{
	int i;
	int status;

	if (!line || !line->env)
		return (1);
	if (!line->arg || !line->arg[0])
		return (print_export(*line->env));

	i = 0;
	status = 0;
	while (line->arg[i])
		status |= handle_export_argument(line, line->arg[i++]);
	return (status);
}
