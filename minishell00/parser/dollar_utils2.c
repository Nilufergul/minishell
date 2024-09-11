#include "../minishell.h"

char *get_res(char *var, t_mini **mini)
{
	char **env;
	char **line;
	int	i;
	char *res;

	env = (*mini)->env;
	res = 0;
	i = 0;
	while (env[i])
	{
		line = ft_split(env[i], '=');
		if (ft_strcmp(var, line[0]) == 0)
		{
			res = ft_strdup(line[1]);
			free(line[0]);
			free(line[1]);
			free(line);
			return (res);
		}
		i++;
	}
	return (res);
}

int get_dollar(char *str, int i, t_mini **mini, char **new_str)
{
	int		j;
	char	*var;
	int		k;
	char	*res;
	char	*temp;

	j = i;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	if (i == j)
		return (i);
	var = (char *)malloc((j - i + 2) * sizeof(char));
	if (!var)
		return (i);
	k = 0;
	while (k < j - i)
	{
		var[k] = str[i + k];
		k += 1;
	}
	var[k] = 0;
	res = get_res(var, mini);
	if (!res)
		return (j);
	temp = ft_strjoin(*new_str, res);
	free(*new_str);
	*new_str = temp;
	free(res);
	return (j - 1);
}

int get_single_quote(char *str, int i, char **new_str)
{
	int		j;
	int		k;
	char	*res;
	char	*temp;

	j = i;
	while (str[j] && str[j] != '\'')
		j++;
	if (i == j)
		return (i);
	res = malloc(j - i + 2);
	if (!res)
		return (i);
	k = 0;
	while (k < j - i)
	{
		res[k] = str[i + k];
		k += 1;
	}
	temp = ft_strjoin(*new_str, res);
	free(*new_str);
	*new_str = temp;
	free(res);
	return (j);
}

int get_double_quote(char *str, int i, char **new_str, t_mini **mini)
{
	char	*temp;

	while (str[i] && str[i] != '\"')
	{
		if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
			i = get_dollar(str, i + 1, mini, new_str);
		else
		{
			temp = ft_calloc(ft_strlen(*new_str) + 2, 1);
			ft_strcpy(temp, *new_str);
			temp[ft_strlen(*new_str)] = str[i];
			temp[ft_strlen(*new_str) + 1] = 0;
			free(*new_str);
			*new_str = temp;
		}
		i++;
	}
	return (i);
}


char *remove_quotes_selman(t_split **split, t_mini **mini)
{
	int i = 0;
	char *temp;
	char *new_str;
	char *str = (*split)->node;
	new_str = malloc(1);
	new_str[0] = 0;

	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
			i = get_dollar(str, i + 1, mini, &new_str);
		else if (str[i] == '\'')
			i = get_single_quote(str, i + 1, &new_str);
		else if (str[i] == '\"')
			i = get_double_quote(str, i + 1, &new_str, mini);
		else
		{
			temp = ft_calloc(ft_strlen(new_str) + 1, 1);
			ft_strcpy(temp, new_str);
			temp[ft_strlen(new_str)] = str[i];
			temp[ft_strlen(new_str) + 1] = 0;
			free(new_str);
			new_str = ft_strdup(temp);
			free(temp);
		}
		i++;
	}
	return (new_str);
}
