#include "minishell.h"

// error mesajları düzenlenmeli.
int	print_syntax_error_quote()
{
	printf("Syntax error. Unclosed quote.\n");
	return (0);
}

int	print_syntax_error_pipe()
{
	printf("Syntax error. Invalid pipe using.\n");
	return (0);
}

int	print_unexpected_char_error()
{
	printf("Unexpected character using.\n");
	return (0);
}

int	print_syntax_error_redir()
{
	printf("Mixed redirect using.\n");
	return (0);
}

