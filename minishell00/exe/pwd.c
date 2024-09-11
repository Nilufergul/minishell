#include "../minishell.h"

void	pwd(void)
{
	char	*s;

	s = getcwd(NULL, 0);
	if (s)
	{
		printf("%s\n", s);
		free(s);
	}
}
