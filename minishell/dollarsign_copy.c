
#include "minishell.h"

// doları kaldırınca meta tyoeını da değiştir

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	ft_isalnum(int i)
{
	if ((i >= '0' && i <= '9') || (i >= 'a' && i <= 'z')
		|| (i >= 'A' && i <= 'Z'))
	{
		return (1);
	}
	return (0);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	slen;
	size_t	max;

	if (!s)
	{
		return (NULL);
	}
	max = 0;
	slen = strlen(s);
	if (start > slen)
	{
		return (strdup(""));
	}
	if (start < slen)
		max = slen - start;
	if (max > len)
		max = len;
	substr = (char *)malloc((sizeof(char)) * max + 1);
	if (!substr)
	{
		return (NULL);
	}
	strlcpy(substr, s + start, max + 1);
	return (substr);
} 
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
	if (str == NULL)
	{
		return (NULL);
	}
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

t_mini *init_mini(t_mini *mini, char** environ)
{
	mini = malloc(sizeof(t_mini));
	if(!mini)
		return (NULL);
	ft_env(mini, environ);
	if(!mini->env)
		return(NULL);
	mini->line = NULL;
	return (mini);
}

int env_size(char **environ)
{
    int i;

    i = 0;
    if (!environ)
        return (0);
    while (environ[i])
        i++;
    return (i);
}

void ft_env(t_mini *mini ,char** environ)
{
	int i;
	
	mini->env = malloc(sizeof(char **) * (env_size(environ) + 1));
	if (!mini->env)
		return;
	i = 0;

	while(environ[i])
	{
		mini->env[i] = strdup(environ[i]);
		i++;
	}
}

// Substring sayısını hesaplayan fonksiyon
int count_substr(const char* str, const char* sub) {
    int count = 0;
    const char *tmp = str;
    int sub_len = strlen(sub);

    while ((tmp = strstr(tmp, sub)) != NULL) {
        count++;
        tmp += sub_len;
    }
    return count;
}

// t_split struct'ındaki node'u yerinde değiştiren fonksiyon
void replace_node_substr(t_split *node_struct, const char *var, const char *value) {
    int old_len, new_len, extra_len;
    char *new_node, *pos;
    const char *str;

    if (!node_struct || !node_struct->node || !var || !value) return;

    old_len = strlen(var);
    new_len = strlen(value);
    extra_len = (new_len > old_len) ? (new_len - old_len) * count_substr(node_struct->node, var) : 0;

    new_node = malloc(strlen(node_struct->node) + extra_len + 1);
    if (!new_node) return;

    pos = new_node;
    str = node_struct->node;

    while (*str) {
        if (strstr(str, var) == str) {
            strcpy(pos, value);
            pos += new_len;
            str += old_len;
        } else {
            *pos++ = *str++;
        }
    }
    *pos = '\0';

    free(node_struct->node);
    node_struct->node = new_node;
}

/*
void	delete_any(t_split *split, char del) // delete the char
{
	size_t	j;

	if (!s1 || !set)
	{
		
	}
	while (*s1 && ft_strchr(set, *s1))
	{
		s1++;
	}
	j = ft_strlen(s1);
	while (j && ft_strchr(set, s1[j]))
	{
		j--;
	}
	
}*/

char *dollar_exp(t_split *split, char *s)
{
	int i;
	int j;
	char *ret; 

	i = 0;
	j = 0;
	while(s[i] != '\0')
	{
		if ((s[i] == '$') && (s[i + 1] != '?') && (ft_isalnum(s[i + 1])))
		{
			i++;
			while((s[i + j]) && (s[i + j] != '\"') && (s[i + j] != '\''))
			{
				j++;
			}
			break;
		}
		i++;
	}
	ret = ft_substr(s, i ,j);
	if(j == 0)
	{
		replace_node_substr(split, "$", ""); // seg
		return NULL;
	}
	return (ret);
}


int	vary_check(t_mini *mini, char *var) 
{
	size_t j;
	
	j = 0;
	while (mini->env[j] != NULL)
	{
		if ((strncmp(mini->env[j], var, strlen(var)) == 0) && mini->env[j][strlen(var)] == '=')
			return (j); // variabşe varsa da env'deki satır 'i'sini döndürüyor
		j++;
	}
	return (-1); // envde aranan variable yok 
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

char	*dollar_checker(t_split *split, char *s, t_mini *mini )
{
	int i;
	char *var;

	i = 0;
	
	if((void*)dollar_exp(split, s))
	{
		if(vary_check(mini, (dollar_exp(split ,s)))) // 0.satır geçsin
		{
			return(value_ret(mini,(vary_check(mini, (dollar_exp(split, s)))))); //value returns //dolap
		}
		return NULL; //aranan variable yok
	}
	return NULL;   
}

void	handle_dollar(t_split *split , t_mini *mini) // line üzerinbde bu değişiklikleri yapan fonksiyonlara gönderilicek
{
	char *var;


	int i;
	i = 0;

	var = ft_strjoin("$", (dollar_exp(split,split->node)));
	while(split->node[i])
	{
		if ((split->node[i] == '$') && ((split->node[i + 1] == ' ') ))
		{
			return; 
		}
		i++;
	}
	if((dollar_checker(split,split->node ,mini)))
	{
		replace_node_substr(split, var, (dollar_checker(split ,split->node,mini)));
	}
	replace_node_substr(split, var, ""); //$jPATH

	free(var);
}

int main(int argc, char** argv,char** environ) 
{
	t_mini *mini;
	(void)argc;
	(void)argv;

	mini = NULL;
	mini = init_mini(mini, environ);
	if(!mini)
		return 0;

    t_split *split = (t_split *)malloc(sizeof(t_split));
    if (!split) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
	
    split->meta = 42;
    split->node = strdup("Hello $'PAT' Welcome to the $'PAT' of programming.");
    if (!split->node) {
        fprintf(stderr, "Memory allocation failed\n");
        free(split);
        return 1;
    }
    split->next = NULL;
	handle_dollar(split , mini);
    printf("Modified node: %s\n", split->node);

    free(split->node);
    free(split);

    return 0;
}

	