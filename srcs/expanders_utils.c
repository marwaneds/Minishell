/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanders_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cortiz <cortiz@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 20:46:20 by cortiz            #+#    #+#             */
/*   Updated: 2023/07/16 20:46:20 by cortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	dollar_sign(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*char_to_str(char c)
{
	char	*str;

	str = ft_calloc(sizeof(char), 2);
	str[0] = c;
	return (str);
}

int	after_dol_lenght(char *str, int j)
{
	int	i;

	i = j + 1;
	while (str[i] != '\0' && str[i] != '$' && str[i] != ' '
		&& str[i] != '\"' && str[i] != '\'' && str[i] != '=' && str[i] != '-'
		&& str[i] != ':')
		i++;
	return (i);
}

size_t	quotes_lenght(char *str)
{
	int		i;
	size_t	ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			ret++;
		}
		i++;
	}
	return (ret);
}

int	is_quotes(char c)
{
	return (c == '\'' || c == '\"');
}
