#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;

	tab = malloc(nmemb * size);
	if (!tab || size == SIZE_MAX || nmemb == SIZE_MAX)
		return (0);
	ft_bzero(tab, nmemb * size);
	return (tab);
}
