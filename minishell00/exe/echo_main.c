
#include "../minishell.h"

int	echo_main(char *s)
{
	int	ind;

	if (!s)
	{
		printf("\n");
		return (0);
	}
	ind = echo_index(s);
	printf("%s", &s[ind]);
	if (ind < 3)
		printf("\n");
	return (1);
}
