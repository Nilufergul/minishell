
#include "pipex.h"

int	echo_main(char *s)
{
	int	ind;

	ind = echo_index(s);
	printf("%s", &s[ind]);
	if (ind < 3)
		printf("\n");
	return (1);
}

/*
int main()
{
	printf("");
	echo_main("--nnnnnn selman selman");
	echo_main("-nnnnnn selman selman");
}
*/
