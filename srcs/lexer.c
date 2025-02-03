#include "minishell.h"

void	lexer_adback(t_lexer **lexer, t_lexer *new)
{
	t_lexer	*back;

	back = *lexer;
	if (!*lexer)
		*lexer = new;
	else
	{
		while (back->next)
			back = back->next;
		back->next = new;
		new->prev = back;
	}
}

int	get_token(char *str, int *i, int *tokken)
{
	if (str[*i] == '<' && str[*i + 1] == '<')
		*tokken = LESS_LESS;
	else if (str[*i] == '>' && str[*i + 1] == '>')
		*tokken = GREAT_GREAT;
	else if (str[*i] == '>')
		*tokken = GREAT;
	else if (str[*i] == '<')
		*tokken = LESS;
	else if (str[*i] == '|')
		*tokken = PIPE;
	else
		*tokken = 0;
	if (*tokken == LESS_LESS || *tokken == GREAT_GREAT)
		*i += 2;
	else if (*tokken)
		*i += 1;
	return (*tokken);
}

int	add_nodee(t_lexer **lexer, char *str, int tokken)
{
	t_lexer		*tmp;
	static int	i = 0;

	tmp = (t_lexer *)malloc(sizeof(t_lexer));
	if (!tmp)
		return (0);
	tmp->str = str;
	tmp->token = tokken;
	tmp->i = i;
	tmp->next = NULL;
	tmp->prev = NULL;
	lexer_adback(lexer, tmp);
	i++;
	return (1);
}

void	add_word(char *str, int *i, t_data *data)
{
	int		j;
	char	*tmp;

	j = *i;
	while (!is_token(str[j]) && !ft_iswhitespace(str[j]) && str[j])
	{
		skip_quotes(&j, str, '\'');
		skip_quotes(&j, str, '\"');
		j++;
	}
	tmp = ft_substr(str, *i, j - *i);
	if (tmp)
		add_nodee(&data->lexer_list, tmp, 0);
	*i = j;
}

int	token_reader(t_data *data)
{
	int		i;
	int		tokken;

	i = 0;
	tokken = 0;
	data->lexer_list = NULL;
	while (data->args[i])
	{
		while (ft_iswhitespace(data->args[i]))
			i++;
		if (get_token(data->args, &i, &tokken))
			add_nodee(&data->lexer_list, NULL, tokken);
		else
			add_word(data->args, &i, data);
	}
	return (1);
}
