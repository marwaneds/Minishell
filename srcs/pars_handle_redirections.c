#include "minishell.h"

char	*join_heredoc(char *str1, char *str2)
{
	char	*ret;
	char	*tmp;

	if (!str2)
		return (ft_strdup(str1));
	tmp = ft_strjoin(str1, " ");
	ret = ft_strjoin(tmp, str2);
	free(tmp);
	free(str2);
	return (ret);
}

int	add_new_redirection(t_lexer *tmp, t_parser_data *parser_data)
{
	t_lexer	*node;
	int		index_1;
	int		index_2;

	node = ft_lexernew(ft_strdup(tmp->next->str), tmp->token);
	if (!node)
		parser_error(1, parser_data->data, parser_data->lexer_list);
	ft_lexeradd_back(&parser_data->redirections, node);
	index_1 = tmp->i;
	index_2 = tmp->next->i;
	ft_lexerdelone(&parser_data->lexer_list, index_1);
	ft_lexerdelone(&parser_data->lexer_list, index_2);
	parser_data->num_redirections++;
	return (0);
}

void	rm_redirections(t_parser_data *parser_data)
{
	t_lexer	*tmp;

	tmp = parser_data->lexer_list;
	while (tmp && tmp->token == 0)
		tmp = tmp->next;
	if (!tmp || tmp->token == PIPE)
		return ;
	if (!tmp->next)
		parser_error(0, parser_data->data, parser_data->lexer_list);
	if (tmp->next->token)
		parser_double_token_error(parser_data->data,
			parser_data->lexer_list, tmp->next->token);
	if ((tmp->token >= GREAT
			&& tmp->token <= LESS_LESS))
		add_new_redirection(tmp, parser_data);
	rm_redirections(parser_data);
}
