/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 18:53:59 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/29 18:55:53 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

char					**ft_recopy(char **arr, size_t *len, size_t n, size_t m)
{
	char		**temp;
	size_t		i;

	i = 0;
	*len += m;
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

char					**ft_asm_read_file(const int fd, char ***arr)
{
	size_t		i;
	size_t		len;
	char		*line;
	int			status;
	int			flag;

	len = 10;
	(*arr) = (char**)malloc(sizeof(char*) * len + 1);
	ft_bzero(*arr, sizeof(*arr));
	i = 0;
	line = NULL;
	while ((status = get_next_line(fd, &line)) > 0)
	{
		flag = status;
		(i == len) ? (*arr) = ft_recopy((*arr), &len, i, MEMORY_COEF) : 0;
		(*arr)[i++] = ft_strdup(line);
		ft_strdel(&line);
	}
	if (flag == 1)
		(*arr)[i++] = ft_strdup("\0");
	(*arr)[i] = NULL;
	ft_strdel(&line);
	return ((status == -1) ? NULL : *arr);
}

void					ft_init(int fd, t_valid *valid)
{
	valid->l_num = 0;
	valid->errors = 0;
	valid->name = 0;
	valid->cmmt = 0;
	valid->flag = 1;
	valid->file = NULL;
	if ((ft_asm_read_file(fd, &valid->file)) == NULL)
		ft_exception("Failed to read from file.", 2);
	g_asm.label = NULL;
	g_asm.oper = NULL;
	g_asm.instr_counter = 0;
	g_asm.prog_size = 0;
	g_asm.instructions = NULL;
	g_asm.name = NULL;
	g_asm.cmmt = NULL;
}

t_ft_valid_layers		*ft_init_layers(void)
{
	t_ft_valid_layers		*arr;

	arr = (t_ft_valid_layers*)malloc(sizeof(t_ft_valid_layers)
			* VALIDATION_LAYERS_AMOUNT + 1);
	arr[0] = ft_lexical_validation;
	arr[1] = ft_syntax_validation;
	arr[2] = ft_logical_validation;
	arr[3] = NULL;
	return (arr);
}
