#include "libft.h"
#include "../asm.h"

static	char		**ft_realoc_n_copy(char **arr, size_t *len, size_t n, size_t memory_coef)
{
	char		**temp;
	size_t		i;

	i = 0;
	*len += memory_coef;
	temp = (char**)malloc((*len) * sizeof(char*));
	while (i < n)
	{
		temp[i] = ft_strdup(arr[i]);
		i++;
	}
	temp[i] = NULL;
	ft_free_bidarr(arr, i);
	return (temp);
}

char 				**ft_read_file(const int fd)
{
	char 		**arr;
	size_t		i;
	size_t		len;
	char		*line;

	len = 10;
	arr = (char**)malloc(sizeof(char*) * len);
	i = 0;
	line = ft_strnew(0);
	while (get_next_line(fd, &line, ft_strnew(0)) > 0)
	{
		(i == len) ? arr = ft_realoc_n_copy(arr, &len, i, MEMORY_COEF) : 0;
		arr[i++] = ft_strdup(line);
	}
	arr[i] = NULL;
	ft_memdel((void**)&line);
	return (arr);
}
