#include "minishell.h"

void	skip_quotes(int *i, char *str, char quote)
{
	if (str[*i] == quote)
	{
		*i += 1;
		while (str[*i] && str[*i] != quote)
			*i += 1;
	}
}

int	is_token(char c)
{
	return (c == '<' || c == '>' || c == '|');
}
