#include "../minishell.h"

void	quotes(t_split *split)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	while (split->node[i])
	{
		if (split->node[i] == '\"' || split->node[i] == '\'')
		{
			quote = split->node[i];
			j = i;
			i++;
			while (split->node[i] && split->node[i] != quote)
				i++;
			if (split->node[i] == quote)
			{
				char_remove(split, j);
				char_remove(split, i - 1);
				i--;
			}
		}
		else
			i++;
	}
}

void	char_remove(t_split *split, int i)
{
	int	len;

	len = ft_strlen(split->node);
	if (i < 0 || i >= len)
		return ;
	ft_memmove(split->node + i, split->node + i + 1, len - i);
	split->node[len - 1] = '\0';
}

void	remove_quotes(t_split *split)
{
	while (split)
	{
		quotes(split);
		split = split->next;
	}
}

void	dollar_quest(t_split *split)
{
	int	i;

	i = 0;
	while (split->node[i] != '\0')
	{
		if ((split->node[i] == '$') && (split->node[i + 1] == '?')
			&& !(ft_isalnum(split->node[i + 2])))
		{
			printf("dolar soru işareti çalışcak.exit status\n"); //?????!!!!!!!!!!
			replace_node_substr(split, "$?", "mock_exitstatus"); //?????!!!!!!!!!!
		}
		i++;
	}
}

void	expander(t_split *split, t_mini *mini)// $'PAT'   kontrol edilcek // dolar kontrolü burada başlıyor.
{
	int	flag;

	flag = 0;
	while (split)
	{
		if (split->meta == DOLLAR)
		{
			if (closed_quotes_index(split->node)) // dolar tırnak grubu içinde mi kalıyor
			{
				if ((quoted_dollar(split) && !closed_quotes_index(split->node)))
					replace_node_substr(split, "$", "");
				if (closed_quotes_index(split->node) == '\'') // dolar hangi tırnak içinde kalıyor (tek tırnak içindeki dolar çalışmıyor
					flag = 1;
			}
			else if (quoted_dollar(split))
				replace_node_substr(split, "$", "");
			if (flag == 0)
			{
				dollar_quest(split); // $? çalıştırıyor
				handle_dollar(split, mini); // expand edilicek dolarları çalıştırıyor.
			}
			split->meta = EXCEPT;
		}
		flag = 0;
		split = split->next;
	}
}
