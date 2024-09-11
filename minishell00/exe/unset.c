#include "../minishell.h"

int	is_valid_unset(const char *arg)
{
	int	i;

	if (arg == NULL || *arg == '\0' || !ft_isalpha(arg[0]))
	{
		printf("unset: `%s': not a valid identifier\n", arg);
		return (0);
	}
	i = 0;
	while (arg[i] != '\0')
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
	char	**new_env;
	int		k;
	int		m;

	env_size = 0;
	while (env[env_size] != NULL)
		env_size++;
	new_env = (char **)malloc(sizeof(char *) * env_size);
	if (new_env == NULL)
		return (env);
	k = -1;
	m = -1;
	while (env[++k] != NULL)
	{
		if (k != index)
		{
			new_env[++m] = env[k];
		}
	}
	new_env[m] = NULL;
	free(env[index]);
	free(env);
	return (new_env);
}

void	remove_var(char ***env, const char *arg)
{
	int		j;
	size_t	arg_len;

	j = 0;
	arg_len = ft_strlen(arg);
	while ((*env)[j] != NULL)
	{
		if (ft_strncmp((*env)[j], arg, arg_len) == 0
			&& (*env)[j][arg_len] == '=')
		{
			*env = remove_env_var(*env, j);
			break ;
		}
		j++;
	}
}

void	ft_unset(t_line *line)
{
	int	i;

	if (line == NULL || line->env == NULL || line->arg == NULL)
		return ;
	i = 0;
	while (line->arg[i] != NULL)
	{
		if (is_valid_unset(line->arg[i]))
		{
			remove_var(line->env, line->arg[i]);
		}
		i++;
	}
}
