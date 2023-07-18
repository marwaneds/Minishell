/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cortiz <cortiz@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 20:46:48 by cortiz            #+#    #+#             */
/*   Updated: 2023/07/16 20:46:49 by cortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
