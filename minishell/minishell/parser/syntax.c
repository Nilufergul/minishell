
#include "../minishell.h"

int pipex_check(t_mini *mini)
{
	char *str;
	int i;

	i = 0;
	str = mini->line;
	while(str[i])
	{
		if(str[i] == '|')
		{
			if(str[i+1] != '\0' && str[i+1] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

void syntax_check(t_mini *mini)
{
	if(pipex_check(mini))
		printf("eroor");
}