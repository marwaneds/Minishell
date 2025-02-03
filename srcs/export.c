#include "minishell.h"

int	variable_exist(t_data *data, char *str)
{
	int	i;

	i = 0;
	if (str[equal_sign(str)] == '\"' || str[equal_sign(str)] == '\'')
		loop_through_str(str);
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i],
				str, equal_sign(data->envp[i])) == 0)
		{
			free(data->envp[i]);
			data->envp[i] = ft_strdup(str);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_parameter(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (export_error(str));
	if (equal_sign(str) == 0)
		return (EXIT_FAILURE);
	if (str[0] == '=')
		return (export_error(str));
	while (str[i] != '=')
	{
		if (check_valid_identifier(str[i]))
			return (export_error(str));
		i++;
	}
	return (EXIT_SUCCESS);
}

char	**whileloop_add_var(char **arr, char **rtn, char *str)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		if (arr[i + 1] == NULL)
		{
			rtn[i] = ft_strdup(str);
			rtn[i + 1] = ft_strdup(arr[i]);
		}
		else
			rtn[i] = ft_strdup(arr[i]);
		if (rtn[i] == NULL)
		{
			free_arr(rtn);
			return (rtn);
		}
		i++;
	}
	return (rtn);
}

char	**add_var(char **arr, char *str)
{
	char	**rtn;
	size_t	i;

	i = 0;
	if (str[equal_sign(str)] == '\"' || str[equal_sign(str)] == '\'')
		loop_through_str(str);
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 2);
	if (!rtn)
		return (NULL);
	i = 0;
	whileloop_add_var(arr, rtn, str);
	return (rtn);
}

int	builtin_export(t_data *data, t_cmds *cmd)
{
	char	**tmp;
	int		i;

	i = 1;
	if (!cmd->str[1] || cmd->str[1][0] == '\0')
		export_env_declare(data);
	else
	{
		while (cmd->str[i])
		{
			if (check_parameter(cmd->str[i]) == 0
				&& variable_exist(data, cmd->str[i]) == 0)
			{
				if (cmd->str[i])
				{
					tmp = add_var(data->envp, cmd->str[i]);
					free_arr(data->envp);
					data->envp = tmp;
				}
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
