#include "minishell.h"

t_cmds	*ft_cmdsnew(char **str, int num_redir, t_lexer *redir)
{
	t_cmds	*new_element;

	new_element = (t_cmds *)malloc(sizeof(t_cmds));
	if (!new_element)
		return (0);
	new_element->str = str;
	new_element->builtin = str[0];
	new_element->hd_file_name = NULL;
	new_element->num_redirections = num_redir;
	new_element->redirections = redir;
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}

void	ft_cmdsadd_back(t_cmds **lst, t_cmds *new)
{
	t_cmds	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void	ft_cmdsclear(t_cmds **lst)
{
	t_cmds	*tmp;
	t_lexer	*redirections_tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		redirections_tmp = (*lst)->redirections;
		ft_lexerclear(&redirections_tmp);
		if ((*lst)->str)
			free_arr((*lst)->str);
		if ((*lst)->hd_file_name)
			free((*lst)->hd_file_name);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

t_cmds	*ft_cmdsfirst(t_cmds *map)
{
	if (!map)
		return (NULL);
	while (map->prev != NULL)
		map = map->prev;
	return (map);
}
