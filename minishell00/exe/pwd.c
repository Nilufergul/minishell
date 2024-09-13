#include "../minishell.h"

int	pwd(void)
{
	char	*s;

	s = getcwd(NULL, 0);
	if (s)
	{
		printf("%s\n", s);
		free(s);
	}
	return (0);
}
