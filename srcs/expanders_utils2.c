#include "minishell.h"

int	question_mark(char **tmp)
{
	free(*tmp);
	*tmp = ft_itoa(g_global.error_num);
	return (ft_strlen(*tmp) + 1);
}

bool	is_between_single(char *str, char c)
{
	int		i;
	bool	is_between;

	i = 0;
	is_between = false;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
			skip_quotes(&i, str, '\"');
		if (str[i] == '\'')
		{
			is_between = !is_between;
		}
		else if (str[i] == c && is_between)
			return (false);
		i++;
	}
	return (true);
}

int	remove_quotes(char *cpy, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cpy[i])
	{
		if (cpy[i] == '\"')
			while (cpy[++i] && cpy[i] != '\"')
				str[j++] = cpy[i];
		if (cpy[i] == '\"')
			i++;
		if (cpy[i] == '\'')
			while (cpy[++i] && cpy[i] != '\'')
				str[j++] = cpy[i];
		if (cpy[i] == '\'')
			i++;
		if (!is_quotes(cpy[i]))
			while (cpy[i] && !is_quotes(cpy[i]))
				str[j++] = cpy[i++];
	}
	return (j);
}

int	loop_through_str(char *str)
{	
	int		i;
	char	*cpy;

	cpy = ft_strdup(str);
	if (!cpy)
		return (0);
	i = remove_quotes(cpy, str);
	str[i] = '\0';
	free(cpy);
	return (1);
}
