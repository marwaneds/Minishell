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
