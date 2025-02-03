#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ret;

	ret = (char *)s;
	i = 0;
	while (s[i])
	{
		if ((char)c == s[i])
			return (&ret[i]);
		i++;
	}
	if (ret[i] == c)
		return (&ret[i]);
	return (0);
}
