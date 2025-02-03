int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

/*#include <ctype.h>
#include <stdio.h>
int main()
{
	char c;

	c = 'Q';
	printf("MAJ : %d\n", ft_isalpha(c));
	c = 'H';
	printf("autre Maj : %d\n", ft_isalpha(c));
	c = 'q';
	printf("min : %d\n", ft_isalpha(c));
	c = '+';
	printf("pas alph : %d\n", ft_isalpha(c));
}*/
