/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cortiz <cortiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 08:41:48 by mel-faqu          #+#    #+#             */
/*   Updated: 2023/07/17 08:57:07 by cortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_data *data, t_cmds *cmd, char *str)
{
	if (!ft_strcmp(str, "echo"))
		return (builtin_echo(data, cmd));
	else if (!ft_strcmp(str, "cd"))
		return (builtin_cd(data, cmd));
	else if (!ft_strcmp(str, "pwd"))
		return (builtin_pwd(data, cmd));
	else if (!ft_strcmp(str, "export"))
		return (builtin_export(data, cmd));
	else if (!ft_strcmp(str, "unset"))
		return (builtin_unset(data, cmd));
	else if (!ft_strcmp(str, "env"))
		return (builtin_env(data, cmd));
	else if (!ft_strcmp(str, "exit"))
		return (builtin_exit(data, cmd));
	return (0);
}
