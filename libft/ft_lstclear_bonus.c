#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*clst;
	t_list	*nlst;

	if (!lst || !del)
		return ;
	clst = *lst;
	while (clst)
	{
		nlst = clst->next;
		del(clst->content);
		free(clst);
		clst = nlst;
	}
	*lst = 0;
}
