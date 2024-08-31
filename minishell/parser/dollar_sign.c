#include "../minishell"

char *dollar_exp(t_split *split, char *s)
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

int vary_check(t_mini *mini, char *var) {
    size_t j;
    j = 0;
    while (mini->env[j] != NULL) {
        if ((strncmp(mini->env[j], var, strlen(var)) == 0) && mini->env[j][strlen(var)] == '=')
            return j;
        j++;
    }
    return -1;
}

char *value_ret(t_mini *mini, int p) {
    char *value;
    if (p == -1)
        return NULL;
    value = strchr(mini->env[p], '=');
    if (value)
        return value + 1;
    return NULL;
}

char *dollar_checker(t_split *split, char *s, t_mini *mini)
{
    char *exp;
    int var_index;

    exp = dollar_exp(split, s);
    if (!exp)
        return NULL;
    var_index = vary_check(mini, exp);
    free(exp);
    if (var_index != -1)
        return value_ret(mini, var_index);
    return NULL;
}

int	handle_dollar(t_split *split, t_mini *mini)
{
    char *exp;
    char *var;
    char *value;

    if (!split || !mini)
        return 0;
    if(!dollar_exp(split, split->node)) // dolardan sonra bosluk varsa
    {
        return 0;
    }
    var = ft_strjoin("$",(dollar_exp(split, split->node)));
    if (!var)
        return 0;
	value = dollar_checker(split, split->node, mini);
    if (value)
        replace_node_substr(split, var, value);
    else
        replace_node_substr(split, var, "");
    free(var);
	return 1;
}

