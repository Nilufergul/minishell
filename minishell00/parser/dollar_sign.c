#include "../minishell.h"

char *dollar_exp(char *s)
{
    int i;
    int j;
    i = 0;
    j = 0;
    while (s[i] != '\0') 
	{
        if ((s[i] == '$') && (ft_isalnum(s[i + 1])))
        {
            i++;
            while (s[i + j] && ft_isalnum(s[i + j]) && s[i +j] != ' ')
            {
                j++;
            }
            break;
        }
        i++;
    }
    if (j == 0)
        return NULL;
    return ft_substr(s, i, j);
}

int vary_check(t_mini *mini, char *var) 
{
    size_t i;
    size_t j;

    i = 0;
    j = 0;
    while (mini->env[j] != NULL) 
    {
        while (mini->env[j][i] == var[i]) 
        {
            i++;
        }
        if (i == ft_strlen(var)) 
            return j;
        j++;
    }
    return -1;
}

char *value_ret(t_mini *mini, int p) 
{
    char *value;
    if (p == -1)
        return NULL;
    value = ft_strchr(mini->env[p], '=');
    if (value)
        return value + 1;
    return NULL;
}

char *dollar_checker(char *s, t_mini *mini)
{
    char *exp;
    int var_index;

    exp = dollar_exp(s);
    if (!exp)
        return NULL;
    var_index = vary_check(mini, exp); //envde vaiable ı arıyor ve hangii satırda olduğunu döndürüyor
    free(exp);
    if (var_index != -1)
        return value_ret(mini, var_index);// envdeki valueu döndürüyor
    return NULL;
}

int	handle_dollar(t_split *split, t_mini *mini) // olman variiablela dolar calıstımrya bakılıcak
{
    char *var;
    char *value;

    if (!split || !mini)
        return 0;
    if(!dollar_exp(split->node)) // dolardan sonra bosluk varsa
    {
        return 0;
    }
    var = ft_strjoin("$",(dollar_exp(split->node))); // doların yanında yazan variable ismini alıyor, ve doğru çalıltığında hepsini silebilmek adına başına dolar ekliyoruz
    if(var[1] == 0 && var[2] == '\0')
    {
	replace_node_substr(split, var, "./minishell"); //$0 çalıştırıyor
    }
    if (!var)
        return 0;
	value = dollar_checker(split->node, mini); //değişkenin değeri env de varsa, valueusunu döndürüyor
    if (value)
        replace_node_substr(split, var, value); // spliti nodeunun içinde var ı bulup value ile değiştiriyor.
    else
        replace_node_substr(split, var, ""); // variable evde yoksa, dolarlı argüman siliniyor.
    free(var);
	return 1;
}

