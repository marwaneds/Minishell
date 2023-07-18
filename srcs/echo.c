/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cortiz <cortiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 08:42:02 by mel-faqu          #+#    #+#             */
/*   Updated: 2023/07/17 08:57:07 by cortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_echo_flags(char **str, int *is_n_flag)
{
	int	i;
	int	j;

	i = 1;
	while (str[i] && str[i][0] == '-')
	{
		j = 1;
		while (str[i][j])
		{
			if (str[i][j] == 'n')
			{
				(*is_n_flag) = 1;
				j++;
			}
			else
				return (i);
		}
		i++;
	}
	return (i);
}

static int	skip_echo_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_iswhitespace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(t_data *data, t_cmds *cmd)
{
	int		is_n_flag;
	int		i;

	(void) data;
	is_n_flag = 0;
	i = parse_echo_flags(cmd->str, &is_n_flag);
	while (cmd->str[i])
	{
		while (cmd->str[i + 1] && skip_echo_spaces(cmd->str[i]))
			i++;
		ft_putstr_fd(cmd->str[i], 1);
		if (cmd->str[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!is_n_flag)
		ft_putchar_fd('\n', 1);
	return (0);
}
