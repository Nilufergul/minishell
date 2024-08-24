
#include "../minishell.h"

//dolar is working kontrolü eklencek. libft functionlarına dönüştürülcek

/*char *dolar_exp(t_mini *mini) // çalışmıyo,dolar varsa ve expansiona uygunsa, variablein değerini string olarak döndürüyor, dolar kadar girsin ve dolarları silerim
{
	int i; // sonra bakıcaz
	int j;
	char *var;
	char *ret;
	
	i = 0;
	j = 0;
	while(mini->line[i] != '\0')
	{
		if ((mini->line[i] == '$') && ((mini->line[i + 1] != ' ') || (mini->line[i + 1] != '?') || (ft_isalnum(mini->line[i + 1]))))
		{
			mini->line[i] = ' ';
			i++;
			while((mini->line[i] != ' ') && (mini->line[i] != '\"') && (mini->line[i] != '\''))
			{
				j++;
			}
			
		}
		break;
		i++;
	}
	ret =(char*)malloc(sizeof(char)*j);
	j = 0;
	while(i < j)
	{
		ret[j] = mini->line[i];
		i++;
		j++;
	}
	ret[j] = '\0';


		// dolar dolar olarak mı callsııryor? dolar olark calısıyora ve değeğeri yoksa hiçbir şey basmıyır
		// dolar olaarak calısması için yanında bir variabşe olması lazım.
		//dolaar tek tırnak içinde olmicak
		//
		
		// string olarak alıyorsa string olarak baasıyor

	return NULL; //variable yok
}*/

int	vary_check(t_mini *mini, char *var)
{
	size_t i;
	size_t j;
	
	i = 0;
	j = 0;

	while (mini->env[j] != NULL)
	{
		if (strncmp(mini->env[j], var, ft_strlen(var)) == 0 && mini->env[j][ft_strlen(var)] == '=')
			return (j);
		j++;
	}
	return (-1);
}

char *value_ret(t_mini *mini, int p)
{
	if (p == -1)
		return NULL;
		
	char *value = strchr(mini->env[p], '=');
	if (value)
		return value + 1; // '=' işaretinin sonrasını döndür
	return NULL;
}

/*char	*dolar_checker(t_mini *mini)
{
	int i;

	i = 0;
	
	if((void*)dolar_exp(mini))
	{
		if(vary_check(mini, (dolar_exp(mini))))
		{
			return(value_ret(mini,(vary_check(mini, (dolar_exp(mini)))))); //değeri

		}
	}
	return NULL;
}*/
