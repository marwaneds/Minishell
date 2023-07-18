/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cortiz <cortiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 08:43:37 by mel-faqu          #+#    #+#             */
/*   Updated: 2023/07/17 08:57:07 by cortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_data *data, t_cmds *cmd)
{
	int	i;

	(void) cmd;
	i = 0;
	while (data->envp[i])
	{
		ft_putendl_fd(data->envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
