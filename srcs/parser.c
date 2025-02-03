#include "minishell.h"

t_cmds	*initialize_cmd(t_parser_data *parser_data)
{
	char	**str;
	int		i;
	int		arg_size;
	t_lexer	*tmp;

	i = 0;
	rm_redirections(parser_data);
	arg_size = count_args(parser_data->lexer_list);
	str = ft_calloc(arg_size + 1, sizeof(char *));
	if (!str)
		parser_error(1, parser_data->data, parser_data->lexer_list);
	tmp = parser_data->lexer_list;
	while (arg_size > 0)
	{
		if (tmp->str)
		{
			str[i++] = ft_strdup(tmp->str);
			ft_lexerdelone(&parser_data->lexer_list, tmp->i);
			tmp = parser_data->lexer_list;
		}
		arg_size--;
	}
	return (ft_cmdsnew(str,
			parser_data->num_redirections, parser_data->redirections));
}

int	handle_pipe_errors(t_data *data, t_tokens token)
{
	if (token == PIPE)
	{
		parser_double_token_error(data, data->lexer_list,
			data->lexer_list->token);
		return (EXIT_FAILURE);
	}
	if (!data->lexer_list)
	{
		parser_error(0, data, data->lexer_list);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parser(t_data *data)
{
	t_cmds			*node;
	t_parser_data	parser_data;

	data->cmds = NULL;
	count_pipes(data->lexer_list, data);
	if (data->lexer_list->token == PIPE)
		return (parser_double_token_error(data, data->lexer_list,
				data->lexer_list->token));
	while (data->lexer_list)
	{
		if (data->lexer_list && data->lexer_list->token == PIPE)
			ft_lexerdelone(&data->lexer_list, data->lexer_list->i);
		if (handle_pipe_errors(data, data->lexer_list->token))
			return (EXIT_FAILURE);
		parser_data = init_parser_data(data->lexer_list, data);
		node = initialize_cmd(&parser_data);
		if (!node)
			parser_error(0, data, parser_data.lexer_list);
		if (!data->cmds)
			data->cmds = node;
		else
			ft_cmdsadd_back(&data->cmds, node);
		data->lexer_list = parser_data.lexer_list;
	}
	return (EXIT_SUCCESS);
}
