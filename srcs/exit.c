#include "minishell.h"

void	free_data(t_data *data)
{
	free_arr(data->paths);
	free_arr(data->envp);
	free(data->args);
	ft_cmdsclear(&data->cmds);
	free(data->pwd);
	free(data->old_pwd);
	if (data->pipes)
		free(data->pid);
}

int	str_has_only_digits(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

long	ft_atol(const char *str, int *invalid)
{
	size_t	res;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	(*invalid) = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
				sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i++] - 48);
		if ((sign < 0 && res > (size_t)LONG_MAX + 1) \
		|| (sign > 0 && res > LONG_MAX))
		{
			(*invalid) = 1;
			return (0);
		}
	}
	return ((long)(sign * res));
}

static long	get_exit_code(char **str)
{
	long	code;
	int		invalid;

	code = 0;
	if (!str[1])
		code = 0;
	else if (str_has_only_digits(str[1]))
	{
		code = ft_atol(str[1], &invalid);
		if (invalid == 1)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(str[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			code = 255;
		}
	}
	else if (!str_has_only_digits(str[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		code = 255;
	}
	return (code);
}

int	builtin_exit(t_data *data, t_cmds *cmd)
{
	long	code;
	int		args;

	args = ft_tab_len(cmd->str);
	ft_putendl_fd("exit", 2);
	if (args > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	else
	{
		code = get_exit_code(cmd->str);
		free_data(data);
		exit(code);
	}
	return (0);
}
