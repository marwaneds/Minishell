#include "libft.h"

int	ft_iswhitespace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}
