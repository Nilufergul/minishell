
#include "../minishell.h"

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

int count_meta_character(char *str, char s)
{
	int i;
	int count;

	i = 0;
	count = 0;

	while(str[i] != '\0')
	{
		if((str[i] == s && str[i+1] != ' ') ||  (str[i] == s && str[i-1] != ' '))
			count++;
		i++;
	}
	i += count;
	return (i);
}

void adding_space(t_mini *mini, char s)
{
	int i;
	int len;
	int count;

	i = 0;
	len = ft_strlen(mini->line);
	count = count_meta_character(mini->line, s);
	
	char *new_line = malloc(sizeof(char)*(len+count+1));
	if (!new_line) //norm kontrolü yap
		return;

	ft_strlcpy(new_line, mini->line, (len+count+1));
	while(new_line[i] != '\0')
	{
		if((new_line[i] == s && (new_line[i-1] != ' ' && new_line[i-1] != s)))
			shift_and_insert(new_line, &len, (i-1));

		if((new_line[i] == s && (new_line[i+1] != ' ' && new_line[i+1] != s)))
			shift_and_insert(new_line, &len, i);
		i++;
	}
	mini->line = new_line;
}

#include <stdio.h>
int main()
{
	char a[] = "abc<d<<nil";
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