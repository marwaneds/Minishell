/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cortiz <cortiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 08:41:58 by mel-faqu          #+#    #+#             */
/*   Updated: 2023/07/17 08:57:07 by cortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path_ret(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], str, ft_strlen(str)))
			return (ft_substr(data->envp[i], ft_strlen(str),
					ft_strlen(data->envp[i]) - ft_strlen(str)));
		i++;
	}
	return (NULL);
}

int	specific_path(t_data *data, char *str)
{
	char	*tmp;
	int		ret;

	tmp = find_path_ret(str, data);
	ret = chdir(tmp);
	free(tmp);
	if (ret != 0)
	{
		str = ft_substr(str, 0, ft_strlen(str) - 1);
		ft_putstr_fd(str, STDERR_FILENO);
		free(str);
		ft_putendl_fd(" not set", STDERR_FILENO);
	}
	return (ret);
}

void	add_path_to_env(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", data->pwd);
			free(data->envp[i]);
			data->envp[i] = tmp;
		}
		else if (!ft_strncmp(data->envp[i], "OLDPWD=", 7) && data->old_pwd)
		{
			tmp = ft_strjoin("OLDPWD=", data->old_pwd);
			free(data->envp[i]);
			data->envp[i] = tmp;
		}
		i++;
	}
}

int	builtin_cd(t_data *data, t_cmds *cmd)
{
	int		ret;

	if (!cmd->str[1])
		ret = specific_path(data, "HOME=");
	else if (ft_strncmp(cmd->str[1], "-", 1) == 0)
		ret = specific_path(data, "OLDPWD=");
	else
	{
		ret = chdir(cmd->str[1]);
		if (ret != 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd->str[1], STDERR_FILENO);
			perror(" ");
		}
	}
	if (ret != 0)
		return (EXIT_FAILURE);
	change_path(data);
	add_path_to_env(data);
	return (EXIT_SUCCESS);
}
