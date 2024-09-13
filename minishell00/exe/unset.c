#include "../minishell.h"

int	is_valid_unset(const char *arg)
{
	int	i;

	if (!arg || *arg == '\0' || !ft_isalpha(arg[0]))
	{
		printf("unset: `%s': not a valid identifier\n", arg);
		return (0);
	}
	i = 0;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			printf("unset: `%s': not a valid identifier\n", arg);
			return (0);
		}
		i++;
	}
	return (1);
}

char	**remove_env_var(char **env, int index)
{
	int		env_size;
	int		k;
	int		m;
	char	**new_env;

	env_size = 0;
	while (env[env_size])
		env_size++;
	new_env = malloc(sizeof(char *) * env_size);
	if (!new_env)
		return (env);
	k = 0;
	m = 0;
	while (env[k])
	{
		if (k != index)
			new_env[m++] = env[k];
		k++;
	}
	new_env[m] = NULL;
	free(env[index]);
	free(env);
	return (new_env);
}

int	remove_var(char ***env, const char *arg)
{
	int		j;
	size_t	arg_len;

	arg_len = ft_strlen(arg);
	j = 0;
	while ((*env)[j])
	{
		if (!ft_strncmp((*env)[j], arg, arg_len) && (*env)[j][arg_len] == '=')
		{
			*env = remove_env_var(*env, j);
			return (0);
		}
		j++;
	}
	return (0);
}

int	ft_unset(t_line *line)
{
	int	i;
	int	status;

	status = 0;
	if (!line || !line->env || !line->arg)
		return (1);
	i = 0;
	while (line->arg[i])
	{
		if (!is_valid_unset(line->arg[i]))
			status = 1;
		else
			remove_var(line->env, line->arg[i]);
		i++;
	}
	return (status);
}
