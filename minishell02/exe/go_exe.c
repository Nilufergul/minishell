#include "../minishell.h"

char	*get_copy(char *result, char **arr)
{
	char	*cur;
	char	*temp;
	int		i;

	cur = result;
	i = 0;
	while (arr != NULL && arr[i] != NULL)
	{
		temp = ft_strjoin(cur, " ");
		free(cur);
		cur = ft_strjoin(temp, arr[i]);
		free(temp);
		i++;
	}
	return (cur);
}

char	*merge_echo(char **arr)
{
	char	*cur;
	char	*temp;
	int		i;

	if (!arr || !arr[0])
		return (0);
	cur = ft_strdup(arr[0]);
	i = 1;
	while (arr != NULL && arr[i] != NULL)
	{
		temp = ft_strjoin(cur, " ");
		free(cur);
		cur = ft_strjoin(temp, arr[i]);
		free(temp);
		i++;
	}
	return (cur);
}
