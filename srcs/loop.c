/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cortiz <cortiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 20:47:01 by cortiz            #+#    #+#             */
/*   Updated: 2023/07/17 08:57:07 by cortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	implement_data(t_data *data)
{
	data->cmds = NULL;
	data->lexer_list = NULL;
	data->reset = false;
	data->pid = NULL;
	data->heredoc = false;
	g_global.stop_heredoc = 0;
	g_global.in_cmd = 0;
	g_global.in_heredoc = 0;
	parse_envp(data);
	init_signals(0);
	return (1);
}

int	reset_data(t_data *data)
{
	ft_cmdsclear(&data->cmds);
	free(data->args);
	if (data->pid)
		free(data->pid);
	free_arr(data->paths);
	implement_data(data);
	data->reset = true;
	loop(data);
	return (1);
}

int	prepare_executor(t_data *data)
{
	init_signals(1);
	g_global.in_cmd = 1;
	if (data->pipes == 0)
		single_cmd(data->cmds, data);
	else
	{
		data->pid = ft_calloc(sizeof(int), data->pipes + 2);
		if (!data->pid)
			return (ft_error(1, data));
		executor(data);
	}
	g_global.in_cmd = 0;
	return (EXIT_SUCCESS);
}

int	loop(t_data *data)
{
	char	*tmp;

	data->args = readline(READLINE_MSG);
	tmp = ft_strtrim(data->args, " ");
	free(data->args);
	data->args = tmp;
	if (!data->args)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (data->args[0] == '\0')
		return (reset_data(data));
	add_history(data->args);
	if (!count_quotes(data->args))
		return (ft_error(2, data));
	if (!token_reader(data))
		return (ft_error(1, data));
	parser(data);
	prepare_executor(data);
	reset_data(data);
	return (1);
}
