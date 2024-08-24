
#include "../minishell.h"

//dolar is working kontrolü eklencek. libft functionlarına dönüştürülcek

char *dolar_exp(t_mini *mini) // çalışmıyo,dolar varsa ve expansiona uygunsa, variablein değerini string olarak döndürüyor, dolar kadar girsin ve dolarları silerim
{
	int i; // sonra bakıcaz
	int j;
	int a;
	char *ret; 
	
	i = 0;
	j = 0;
	while(mini->line[i] != '\0')
	{
		if ((mini->line[i] == '$') && ((mini->line[i + 1] != ' ') && (mini->line[i + 1] != '?') && (ft_isalnum(mini->line[i + 1]))))
		{
			i++;
			while((mini->line[i] != ' ') && (mini->line[i] != '\"') && (mini->line[i] != '\''))
				j++;
			break;
		}
		i++;
	}
	if(j == 0)
		return NULL; // echo $'path'  =  path  basılıyor
	ret = ft_substr(mini->line, i ,j);
	return (ret);
}

int	vary_check(t_mini *mini, char *var) 
{
	size_t i;
	size_t j;
	
	i = 0;
	j = 0;

	while (mini->env[j] != NULL)
	{
		if (ft_strncmp(mini->env[j], var, ft_strlen(var)) == 0 && mini->env[j][ft_strlen(var)] == '=')
			return (j); // variabşe varsa da env'deki satır 'i'sini döndürüyor
		j++;
	}
	return (-1); // envde aranan variable yok 
}

char *value_ret(t_mini *mini, int p)
{
	if (p == -1)
		return NULL;
		
	char *value = ft_strchr(mini->env[p], '=');
	if (value)
		return value + 1; // '=' işaretinin sonrasını döndür
	return NULL;
}

char	*dolar_checker(t_mini *mini)
{
	int i;

	i = 0;
	if ((mini->line[i] == '$') && ((mini->line[i + 1] == ' ') ))
	{
			return 'a'; 
	}
	if((void*)dolar_exp(mini))
	{
		if(vary_check(mini, (dolar_exp(mini))))
		{
			return(value_ret(mini,(vary_check(mini, (dolar_exp(mini)))))); //value returns

		}
		return NULL; //aranan variable yok
	}
	return NULL;
}

char *handle_dolar(t_mini *mini) // line üzerinbde bu değişiklikleri yapan fonksiyonlara gönderilicek
{
	
	if(dolar_checker(mini) == 'a')
	{
		//dolar dolar görevi yapmıyor ve doları string olarak basıyor
	}
	if((void*)dolar_exp(mini))
	{
		//echo $'path'  =  path  basılıyor  
	}
	if(dolar_checker(mini))
	{
		//aranan varibale yok  yani echo $ffpath  ( new line dönüdrüyor boşş)
	}
	if(!(dolar_checker(mini)))
	{
		return (dolar_checker(mini));
	}
	return NULL;
}
