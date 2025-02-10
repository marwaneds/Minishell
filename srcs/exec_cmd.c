#include "minishell.h"

char	*join_split_str(char **split_str, char *new_str);
char	**resplit_str(char **double_arr);

int	find_cmd(t_cmds *cmd, t_data *data)
{
	int		i;
	char	*mycmd;

	i = 0;
	cmd->str = resplit_str(cmd->str);
	if (!access(cmd->str[0], F_OK))
		execve(cmd->str[0], cmd->str, data->envp);
	while (data->paths[i])
	{
		mycmd = ft_strjoin(data->paths[i], cmd->str[0]);
		if (!access(mycmd, F_OK))
			execve(mycmd, cmd->str, data->envp);
		free(mycmd);
		i++;
	}
	return (cmd_not_found(cmd->str[0]));
}

void	handle_cmd(t_cmds *cmd, t_data *data)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->redirections)
		if (check_redirections(cmd))
			exit(1);
	if (cmd->builtin || cmd->str[0])
	{
		if (!ft_strcmp(cmd->builtin, "echo")
			|| !ft_strcmp(cmd->builtin, "cd")
			|| !ft_strcmp(cmd->builtin, "pwd")
			|| !ft_strcmp(cmd->builtin, "export")
			|| !ft_strcmp(cmd->builtin, "unset")
			|| !ft_strcmp(cmd->builtin, "env")
			|| !ft_strcmp(cmd->builtin, "exit"))
		{
			exit_code = check_builtins(data, cmd, cmd->builtin);
			exit(exit_code);
		}
		else if (cmd->str[0][0] != '\0')
			exit_code = find_cmd(cmd, data);
	}
	exit(exit_code);
}

void	dup_cmd(t_cmds *cmd, t_data *data, int end[2], int fd_in)
{
	if (cmd->prev && dup2(fd_in, STDIN_FILENO) < 0)
		ft_error(4, data);
	close(end[0]);
	if (cmd->next && dup2(end[1], STDOUT_FILENO) < 0)
		ft_error(4, data);
	close(end[1]);
	if (cmd->prev)
		close(fd_in);
	handle_cmd(cmd, data);
}

void	single_cmd(t_cmds *cmd, t_data *data)
{
	int	pid;
	int	status;

	data->cmds = call_expander(data, data->cmds);
	if (cmd->builtin)
	{
		if (!ft_strcmp(cmd->builtin, "cd")
			|| !ft_strcmp(cmd->builtin, "exit")
			|| !ft_strcmp(cmd->builtin, "export")
			|| !ft_strcmp(cmd->builtin, "unset"))
		{
			g_global.error_num = check_builtins(data, cmd, cmd->builtin);
			return ;
		}
	}
	send_heredoc(data, cmd);
	pid = fork();
	if (pid < 0)
		ft_error(5, data);
	if (pid == 0)
		handle_cmd(cmd, data);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_global.error_num = WEXITSTATUS(status);
}
