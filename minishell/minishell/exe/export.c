/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcan <rcan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:36:51 by rcan              #+#    #+#             */
/*   Updated: 2024/09/18 17:36:52 by rcan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid(const char *str)
{
	int	i;

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

int	print_error(const char *arg)
{
	int	len;

	len = ft_strlen(arg);
	write(2, "minishell: export: ", 19);
	write(2, arg, len);
	write(2, " ", 1);
	errno = EINVAL;
	perror("");
	return (1);
}

int	print_export(char **env)
{
	int		i;
	char	*equal_sign;

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

int	handle_export_argument(t_line *line, const char *arg)
{
	char	*equal_sign;

	if (arg[0] == '=')
		return (print_error(arg));
	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		if (!is_valid(arg))
		{
			*equal_sign = '=';
			return (print_error(arg));
		}
		create_update(line->env, arg, equal_sign + 1);
		*equal_sign = '=';
	}
	else if (!is_valid(arg))
		return (print_error(arg));
	return (0);
}

int	ft_export(t_line *line)
{
	int	i;
	int	status;

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
