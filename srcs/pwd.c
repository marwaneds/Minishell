/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cortiz <cortiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 08:43:33 by mel-faqu          #+#    #+#             */
/*   Updated: 2023/07/17 08:57:07 by cortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_data *data, t_cmds *cmd)
{
	char	*path;

	(void) data;
	(void) cmd;
	path = getcwd(NULL, sizeof(NULL));
	if (!path)
		return (1);
	ft_putendl_fd(path, 1);
	free(path);
	return (0);
}
