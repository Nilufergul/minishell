#include "../minishell.h"

int	print_syntax_error_quote(void)
{
	printf("Syntax error. Unclosed quote.\n");
	return (0);
}

int	print_syntax_error_pipe(void)
{
	printf("Syntax error. Invalid pipe using.\n");
	return (0);
}

int	print_unexpected_char_error(void)
{
	printf("Unexpected character using.\n");
	return (0);
}

int	print_syntax_error_redir(void)
{
	printf("Mixed redirect using.\n");
	return (0);
}
// hata kodu döndürücez