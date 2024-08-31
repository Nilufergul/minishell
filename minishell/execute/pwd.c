#include "builtins.h"

void	ft_pwd(void)
{
	char	*s;

	s = getcwd(NULL, 0);
	if (s != NULL)
	{
		printf("%s\n", s);
		free(s); 
	}
	else
	{
		perror("pwd"); 
	}
}
