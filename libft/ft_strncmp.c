#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*sb1;
	unsigned char	*sb2;

	sb1 = (unsigned char *)s1;
	sb2 = (unsigned char *)s2;
	i = 0;
	while (sb1[i] == sb2[i] && i < n)
	{
		if (sb1[i] == '\0' && sb2[i] == '\0')
			return (0);
		i++;
	}
	if (i == n)
		return (0);
	return (sb1[i] - sb2[i]);
}
