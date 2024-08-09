#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ft_strlen ve ft_strdup işlevleri kodunuzdan aynen alınmıştır.
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
    if (!environ)
        return (0);
    while (environ[i])
        i++;
    return (i);
}

typedef struct s_mini
{
    char **env;
} t_mini;

void get_env(t_mini *built)
{
	extern char **environ;
	int i;

	if (!built) // built işaretçisinin NULL olup olmadığını kontrol edin
		return;
	built->env = malloc(sizeof(char *) * (env_size(environ) + 1));
	if (!built->env) // malloc'un başarısız olup olmadığını kontrol edin
		return;
	i = 0;
	while (environ[i])
	{
		built->env[i] = ft_strdup(environ[i]);
		if (!built->env[i]) // ft_strdup'un başarısız olup olmadığını kontrol edin
		{
			while (i-- > 0)
				free(built->env[i]); // Daha önce tahsis edilen belleği serbest bırak
			free(built->env);
			return;
		}
		i++;
	}
	built->env[i] = NULL; // Liste sonunu işaretleyin
}

int main(int argc, char** argv)
{
	t_mini built;
	get_env(&built); // built işaretçisinin adresini geçin
	if (built.env && built.env[0]) // built->env NULL değilse ve ilk eleman geçerli ise
	{
		printf("%s\n", built.env[0]);
	}
	else
	{
		printf("Environment is empty or error occurred.\n");
	}
	
	// Tahsis edilen belleği serbest bırak
	if (built.env)
	{
		int i = 0;
		while (built.env[i])
		{
			free(built.env[i]);
			i++;
		}
		free(built.env);
	}
	
	return 0;
}
