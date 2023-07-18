/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-faqu <mel-faqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 09:00:54 by mel-faqu          #+#    #+#             */
/*   Updated: 2023/07/17 09:00:54 by mel-faqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser_data	init_parser_data(t_lexer *lexer_list, t_data *data)
{
	t_parser_data	parser_data;

	parser_data.lexer_list = lexer_list;
	parser_data.redirections = NULL;
	parser_data.num_redirections = 0;
	parser_data.data = data;
	return (parser_data);
}

void	count_pipes(t_lexer *lexer_list, t_data *data)
{
	t_lexer	*tmp;

	tmp = lexer_list;
	data->pipes = 0;
	while (tmp)
	{
		if (tmp->token == PIPE)
			data->pipes++;
		tmp = tmp->next;
	}
}

int	count_args(t_lexer *lexer_list)
{
	t_lexer	*tmp;
	int		i;

	i = 0;
	tmp = lexer_list;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->i >= 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
