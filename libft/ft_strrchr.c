#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*ret;

	ret = (char *)s;
	len = ft_strlen(s);
	while (len >= 0)
	{
		if ((char)c == s[len])
			return (&ret[len]);
		len--;
	}
	return (0);
}
