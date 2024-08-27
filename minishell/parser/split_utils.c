#include "./minishell.h"

void	skip_quotes(const char *line, int *i)
{
	char	quote;

	quote = line[*i];
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i])
		(*i)++;
}

void	skip_spaces(const char *line, int *i)
{
	while (line[*i] == ' ')
		(*i)++;
}

void	handle_token(const char *line, int *i)
{
	while (line[*i] && line[*i] != ' ' && line[*i] != '\'' && line[*i] != '\"')
		(*i)++;
}