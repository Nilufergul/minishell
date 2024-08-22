
#include "../minishell.h"

/*
int quote_checker_1(t_mini *mini)
{
	int i;
	char quote;
	
	i = 0;
	while(mini->line[0][i])
	{
		if(mini->line[0][i] == '\"' || mini->line[0][i] == '\'')
		{
			quote = mini->line[0][i];
			i++;
			while(mini->line[0][i] && mini->line[0][i] != quote)
			{
				i++;
			}
			if(mini->line[0][i] == '\0')
				return(0);
		}
		i++;
	}
	return(1);
}
*/
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
/*
void pipex_check(t_mini *mini)
{
	char *str;
	int i;

	i = 0;
	str = mini->line[0];
	while(str[i])
	{
		if(str[i] == '|')
		{
			if(str[i+1] != '\0' && str[i+1] == '|')
				printf("error\n");
				//error
		}
		i++;
	}
}
*/
/*
void space(t_mini *mini)
{
	char *str;
	char quote;
	int quote_on;
	int i;

	str = mini->line[0];
	quote_on = 0;
	i = 0;
	while(str[i])
	{
		if(mini->line[0][i] == '\"' || mini->line[0][i] == '\'')
		{
			quote = mini->line[0][i];
			i++;
			while(mini->line[0][i] && mini->line[0][i] != quote)
			{
				i++;
			}
		}
		else if(mini->line[0][i] == ' ')
		{
			printf("%c\n",mini->line[0][i]);
			space_delete(mini->line[0],i);		
		}
		i++;
	}
}*/
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	if (i < size)
		dest[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}
size_t	ft_strlen(const char *str)
{
	size_t	n;

	n = 0;
	while (str[n] != '\0')
	{
		n++;
	}
	return (n);
}
void shift_and_insert(char *str, int *len, int pos)
{
	int j = *len;
	while (j > pos)
	{
		str[j + 1] = str[j];
		j--;
	}
	str[pos+1] = ' ';
	(*len)++;
	str[*len] = '\0';
}
void adding_space(t_mini *mini, char s) //kısaltılması lazım
{
	int i;
	int j;
	int len;
	int count;

	i = 0;
	j = 0;
	count = 0;
	len = ft_strlen(mini->line);

	while(mini->line[i] != '\0')
	{
		if((mini->line[i] == s && mini->line[i+1] != ' ') ||  (mini->line[i] == s && mini->line[i-1] != ' '))
			count++;
		i++;
	}
	i = 0;
	
	char *new_line = malloc(sizeof(char)*(len+count+1)); // new_line a göre aşağıdaki while ı düzenle
	if (!new_line)
		return;

	ft_strlcpy(new_line, mini->line, (len+count+1));

	while(new_line[i] != '\0')
	{
		if((new_line[i] == s && new_line[i-1] != ' '))
			shift_and_insert(new_line, &len, (i-1));

		if((new_line[i] == s && new_line[i+1] != ' '))
			shift_and_insert(new_line, &len, i);
		i++;
	}
	mini->line = new_line;
}
/*void space_delete(char *line, int i)
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
}*/
#include <stdio.h>
int main()
{
	char a[] = "abc<d<nil";
	t_mini *minik;

	minik = (t_mini *)malloc(sizeof(t_mini));
	minik->line = malloc(sizeof(char*)* 20);
	if(minik == NULL)
		return 0;
	minik->line = a;
	//adding_space(minik, '|');
	adding_space(minik, '<');
	printf("%s", minik->line);
}