#include "libft.h"

char		*ft_rstrip(char *str)
{
	size_t		i;
	char		*temp;

	temp = NULL;
	i = ft_strlen(str) - 1;
	while (str[i] == ' ' || str[i] == '\t')
		i--;
	if ((temp = ft_strsub(str, i, ft_strlen(str) - i)) == NULL)
		return (NULL);
	return (temp);
}