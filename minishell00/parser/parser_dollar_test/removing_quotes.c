#include "../minishell.h"

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
			//replace_node_substr(split, "$?", "mock_exitstatus"); //?????!!!!!!!!!!
		}
		i++;
	}
}

void	expander(t_split *split, t_mini *mini)// $'PAT'   kontrol edilcek // dolar kontrolü burada başlıyor.
{

	while (split)
	{
		if (split->meta == DOLLAR)
		{
			split->node = remove_quotes_selman(&split, &mini);
			split->meta = EXCEPT;
		}
		split = split->next;
	}
}
