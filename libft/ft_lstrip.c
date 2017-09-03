#include "libft.h"

char		*ft_lstrip(char *str)
{
	size_t		i;
	char		*temp;

	temp = NULL;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if ((temp = ft_strsub(str, i, ft_strlen(str) - i)) == NULL)
		return (NULL);
	return (temp);
}