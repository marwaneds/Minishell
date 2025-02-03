#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*hay;

	hay = (char *)haystack;
	i = 0;
	j = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	if ((!len || !haystack) && len == 0)
		return (NULL);
	while (haystack[i])
	{
		while (haystack[i + j] == needle[j] && haystack[i + j] && (i + j) < len)
			j++;
		if (needle[j] == '\0')
			return (&hay[i]);
		i++;
		j = 0;
	}
	return (0);
}
