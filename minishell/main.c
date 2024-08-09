
#include "lib/minishell.h"

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

char	*ft_strdup(const char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = ft_strlen(s);
	str = (char *)malloc(sizeof(*str) * (j + 1));
	if (!str)
		return (NULL);
	while (i < j)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int env_size(char **environ)
{
    int i;

    i = 0;
    if(!environ)
        return (0);
	
    while(environ[i])
        i++;
    return (i);
}
 void ft_env(t_mini *built)
{
	int i;
	i = 0;
	while(built->env[i])
	{
		printf("%s\n", built->env[i]);
		i++;
	}
}

void get_env(t_mini *built)
{
	extern char **environ;
	int i;

	built->env = malloc(sizeof(char **) * (env_size(environ) + 1));
	if (!built->env)
		return;
	i = 0;

	while(environ[i])
	{
		built->env[i] = ft_strdup(environ[i]);
		i++;
	}
}

int main(int argc, char** argv)
{
	t_mini	*built;
	built = (t_mini *)malloc(sizeof(t_mini));
	get_env(built);
	ft_env(built);
}