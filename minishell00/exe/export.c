#include "../minishell.h"

int	is_valid(const char *str)
{
	int	i;

	if (str == NULL || *str == '\0' || *str == '=' || !ft_isalpha(*str))
		return (0);
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_export(char **env)
{
	int		i;
	char	*equal_sign;

	i = 0;
	while (env[i] != NULL)
	{
		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign != NULL)
		{
			*equal_sign = '\0';
			printf("declare -x %s=\"%s\"\n", env[i], equal_sign + 1);
			*equal_sign = '=';
		}
		else
		{
			printf("declare -x %s\n", env[i]);
		}
		i++;
	}
}

int	is_valid_identifier(const char *arg)
{
	if (!is_valid(arg))
	{
		printf("export: `%s': not a valid identifier\n", arg);
		return (0);
	}
	return (1);
}

void	handle_export_argument(t_line *line, const char *arg)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign != NULL)
	{
		*equal_sign = '\0';
		if (is_valid_identifier(arg))
			create_update(line->env, arg, equal_sign + 1);
		*equal_sign = '=';
	}
	else
	{
		if (is_valid_identifier(arg))
			create_update(line->env, arg, "");
	}
}

void	ft_export(t_line *line)
{
	int	i;

	if (line == NULL || line->env == NULL)
		return ;
	if (line->arg == NULL || line->arg[0] == NULL)
	{
		print_export(*line->env);
		return ;
	}
	i = 0;
	while (line->arg[i] != NULL)
	{
		handle_export_argument(line, line->arg[i]);
		i++;
	}
}
