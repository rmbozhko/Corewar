/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 21:39:32 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/29 21:40:49 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../asm.h"

static	char	**ft_recopy(char **arr, size_t *len, size_t n, size_t mem_coef)
{
	char		**temp;
	size_t		i;

	i = 0;
	*len += mem_coef;
	temp = (char**)malloc((*len) * (sizeof(char*) + 1));
	while (i < n)
	{
		temp[i] = ft_strdup(arr[i]);
		i++;
	}
	temp[i] = NULL;
	ft_free_bidarr(arr, i);
	return (temp);
}

char			**ft_read_file(const int fd, char **arr)
{
	size_t		i;
	size_t		len;
	char		*line;
	int			status;
	int			flag;

	len = 10;
	arr = (char**)malloc(sizeof(char*) * len + 1);
	i = 0;
	line = NULL;
	while ((status = get_next_line(fd, &line)) > 0)
	{
		flag = status;
		(i == len) ? arr = ft_recopy(arr, &len, i, MEMORY_COEF) : 0;
		arr[i++] = ft_strdup(line);
		ft_strdel(&line);
	}
	if (flag == 1)
		arr[i++] = ft_strdup("\0");
	arr[i] = NULL;
	ft_strdel(&line);
	return ((status == -1) ? NULL : arr);
}
