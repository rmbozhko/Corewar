#include "libft.h"

char		*ft_strip(char *str)
{
	char		*temp;
	char		*string;

	temp = ft_lstrip(str);
	string = temp;
	temp = ft_rstrip(temp);
	ft_memdel((void**)&string);
	return (temp);
}