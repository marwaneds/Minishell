#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t destsize)
{
	size_t	c;
	size_t	d;

	if (!destsize)
		return (ft_strlen(src));
	if (destsize <= ft_strlen(dst))
		return (destsize + ft_strlen(src));
	c = ft_strlen(dst);
	d = 0;
	while (src[d] && c + 1 < destsize)
	{
		dst[c] = src[d];
		c++;
		d++;
	}
	dst[c] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[d]));
}
