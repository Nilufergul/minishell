#include "lib/minishell.h"

char	*dolar_checker(t_mini *mini)
{
	int i;

	i = 0;
	//gelen girdiyi dolar checke gönder
	if(dolar_exp(mini))
	{
		if(vary_check(mini, (dolar_exp(mini))))
		{
			return(value_ret(mini ,(vary_check(mini, (dolar_exp(mini)))))); //değeri

		}
	}
	return NULL;
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



int		vary_check(t_mini *mini, char *var) // env içinde variable ismi arıyor varsa yerini veriyor
{
	int i;
	int j;
	
	i = 0;
	j = 0;

	while (mini->env[j][0] != '\0')
	{
		if(mini->env[j][0] == var[0])
		{
			while(mini->env[j][i])
			{
				if(mini->env[j][i] == var[i])
				i++;  
			}
			if (ft_strlen(var) == i)
			{
				return(j); //variableın yeri
			}
			else
				i = 0;
		}
		j++;
	}
	return (0); // aranan variable env'da mevcut değil
}

char *dolar_exp(t_mini *mini) // dolar varsa ve expansiona uygunsa, variablein değerini string olarak döndürüyor
{
	int i;
	char *var;
	char *ret;
	
	i = 0;
	while(mini->line[i] != '\0')
	{
		if (mini->line[i] == '$' && (mini->line[i + 1] != ' ') || (mini->line[i + 1] <= 9 && mini->line[i + 1] >= 13))
		{
			i++;
			while (mini->line[i] != '=')


		

		}
	}
		// dolar dolar olarak mı callsııryor? dolar olark calısıyora ve değeğeri yoksa hiçbir şey basmıyır
		// dolar olaarak calısması için yanında bir variabşe olması lazım.
		//dolaar tek tırnak içinde olmicak
		//
		
		// string olarak alıyorsa string olarak baasıyor

	i = 0;
	if (vary_check(mini, var) != 0)
	{
		while (mini->env[vary_check(mini, var)][ft_len(var + 1 + i)])
		{
			ret = ft_strdup(mini->env[vary_check(mini, var)][ft_len(var + 2 + i)]);
			i++; 
		}
	}
	return NULL; //variable yok
}

char *value_ret(t_mini *mini , int p) //double pointerda değişkenin satırının şndeksini veriyoruz, ve değeri string olarak döndürüyor.
{
	int i;

	i = 0;
	while (mini->env[p][i])
	{
		if (mini->env[p][i] == '=')
		{
			i++;
			return(mini->env[p]); //??
		}
		mini->env[p]++;
	}
	return NULL;
}




int main()
{
	char a[] = "|ab|c   ashjk    ";
	t_mini *mini;

	mini = (t_mini *)malloc(sizeof(t_mini));
	mini->line = malloc(sizeof(char)*20); 
	
	/*get_env(mini, environ);
	ft_env(mini);*/

	if(mini == NULL)
		return 0;
	mini->line = a;
	pipex_check(mini);
}