#include "minishell.h"

int	find_pwd(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], "PWD=", 4))
			data->pwd = ft_substr(data->envp[i],
					4, ft_strlen(data->envp[i]) - 4);
		if (!ft_strncmp(data->envp[i], "OLDPWD=", 7))
			data->old_pwd = ft_substr(data->envp[i],
					7, ft_strlen(data->envp[i]) - 7);
		i++;
	}
	return (1);
}

char	*find_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
		i++;
	}
	return (ft_strdup("\0"));
}

int	parse_envp(t_data *data)
{
	char	*path_from_envp;
	int		i;
	char	*tmp;

	path_from_envp = find_path(data->envp);
	data->paths = ft_split(path_from_envp, ':');
	free(path_from_envp);
	i = 0;
	while (data->paths[i])
	{
		if (ft_strncmp(&data->paths[i][ft_strlen(data->paths[i]) - 1],
			"/", 1) != 0)
		{
			tmp = ft_strjoin(data->paths[i], "/");
			free(data->paths[i]);
			data->paths[i] = tmp;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
