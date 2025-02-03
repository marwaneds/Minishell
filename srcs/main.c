#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1 || argv[1])
	{
		printf("No arguments please\n");
		exit(0);
	}
	data.envp = ft_arrdup(envp);
	find_pwd(&data);
	implement_data(&data);
	loop(&data);
	return (0);
}
