
#include "../minishell.h"

int quote_checker_1(t_mini *mini)
{
	int i;
	char quote;
	
	i = 0;
	while(mini->line[i])
	{
		if(mini->line[i] == '\"' || mini->line[i] == '\'')
		{
			quote = mini->line[i];
			i++;
			while(mini->line[i] && mini->line[i] != quote)
			{
				i++;
			}
			if(mini->line[i] == '\0')
				return(0);
		}
		i++;
	}
	return(1);
}
/*
void meta_sep(t_mini *mini) // |cat<a   -> | cat < a  çalışmıyo0000
{
	char *str;
	int i;
	int count;

	str = mini->line[0];
	
	i = 0;
	count = 0;
	while(str[i])
	{
		if(mini->line[0][i] == '|' || mini->line[0][i] == '>' || mini->line[0][i] == '<' ||
		mini->line[0][i] == '>>' || mini->line[0][i] == '<<')
		{
			while(mini->line[0][i] && mini->line[0][i] != quote)
			{
				i++;
			}
		}
		else if(mini->line[0][i] == ' ')
		{
			space_delete(mini->line[0],i);		
		}
		i++;
	}
}*/

void space(t_mini *mini)
{
	char *str;
	char quote;
	int quote_on;
	int i;

	str = mini->line;
	quote_on = 0;
	i = 0;
	while(str[i])
	{
		if(mini->line[i] == '\"' || mini->line[i] == '\'')
		{
			quote = mini->line[i];
			i++;
			while(mini->line[i] && mini->line[i] != quote)
			{
				i++;
			}
		}
		else if(mini->line[i] == ' ')
		{
			printf("%c\n",mini->line[i]);
			space_delete(mini->line,i);		
		}
		i++;
	}
}

void space_delete(char *line, int i)
{
	int j;
	int k;
	int count;
	
	count = 0;
	j = i;
	k = 0;
	if(line[i+1] != ' ')
		return;
	while(line[j] && line[j] == ' ')
	{
		count++;
		j++;
	}
	count--;
	while(count-- != 0)
	{
		k = j--;
		while(line[k] != '\0')
		{
			line[k-1] = line[k];
			k++;
		}
		line[k-1] = '\0';
	}
}

/*int main()
{
	char a[] = "a	bcashjk";
	t_mini *minik;

	minik = (t_mini *)malloc(sizeof(t_mini));
	minik->line = malloc(sizeof(char*));
	if(minik == NULL)
		return 0;
	minik->line = a;
	space(minik);
	printf("%s\n",minik->line);
}
*/