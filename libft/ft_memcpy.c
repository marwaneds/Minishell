#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	void	*odest;

	if (!dst && !src)
		return (dst);
	odest = dst;
	i = 0;
	while (i < n)
	{
		*(char *)dst = *(char *)src;
		i++;
		dst++;
		src++;
	}
	return (odest);
}
