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
