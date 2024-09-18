/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcan <rcan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:36:49 by rcan              #+#    #+#             */
/*   Updated: 2024/09/18 17:36:50 by rcan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_realloc(void *ptr, size_t current_size, size_t new_size)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	if (current_size < new_size)
		ft_memcpy(new_ptr, ptr, current_size);
	else
		ft_memcpy(new_ptr, ptr, new_size);
	free(ptr);
	return (new_ptr);
}

void	add_env_variable(char ***env, int i, const char *name,
					const char *value)
{
	size_t	name_len;
	size_t	value_len;
	size_t	total_len;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	total_len = name_len + value_len + 2;
	*env = ft_realloc(*env, sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
	if (*env == NULL)
		return ;
	(*env)[i] = malloc(total_len);
	if ((*env)[i] == NULL)
		return ;
	ft_strlcpy((*env)[i], name, total_len);
	(*env)[i][name_len] = '=';
	ft_strlcpy((*env)[i] + name_len + 1, value, total_len - name_len - 1);
	(*env)[i + 1] = NULL;
}

void	update_env_variable(char **env, int i,
						const char *name, const char *value)
{
	size_t	name_len;
	size_t	value_len;
	size_t	total_len;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	total_len = name_len + value_len + 2;
	free(env[i]);
	env[i] = malloc(total_len);
	if (env[i] == NULL)
		return ;
	ft_strlcpy(env[i], name, total_len);
	env[i][name_len] = '=';
	ft_strlcpy(env[i] + name_len + 1, value, total_len - name_len - 1);
}

void	create_update(char ***env, const char *name, const char *value)
{
	int		i;
	size_t	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while ((*env)[i] != NULL)
	{
		if (ft_strncmp((*env)[i], name, name_len) == 0 \
						&& (*env)[i][name_len] == '=')
		{
			update_env_variable(*env, i, name, value);
			return ;
		}
		i++;
	}
	add_env_variable(env, i, name, value);
}

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
