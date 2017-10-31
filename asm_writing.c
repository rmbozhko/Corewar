/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_writing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 18:56:12 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/29 19:02:24 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

t_header		*init_header(void)
{
	t_header		*header;

	header = (t_header *)malloc(sizeof(t_header));
	ft_bzero(header, sizeof(header));
	ft_bzero(header->prog_name, PROG_NAME_LENGTH);
	ft_bzero(header->comment, COMMENT_LENGTH);
	header->magic = move_bits(COREWAR_EXEC_MAGIC);
	ft_memcpy(header->prog_name, g_asm.name, ft_strlen(g_asm.name));
	header->prog_size = move_bits(g_asm.prog_size);
	ft_memcpy(header->comment, g_asm.cmmt, ft_strlen(g_asm.cmmt));
	return (header);
}

void			ft_write_gen_info(int fd)
{
	t_header		*header;
	void			*temp;

	header = init_header();
	temp = header;
	write(fd, temp, sizeof(t_header));
	ft_memdel((void**)&header);
}

void			ft_write_instructions(t_operations *oper, char **str)
{
	t_arg		**arg;
	size_t		i;

	arg = oper->args;
	i = 0;
	**str = (oper->command + 1);
	(*str)++;
	if (oper->cod_byte != 0)
	{
		(**str) = (oper->cod_byte);
		(*str)++;
	}
	while (arg[i])
	{
		ft_handle_args(arg[i], str, oper);
		i++;
	}
}

char			*ft_prepare_for_writing(char *s_file)
{
	char		*cor_file;
	char		*temp;
	size_t		index;
	char		*str;

	str = ft_reverse_str(s_file);
	index = ft_strchr(str, '.') - str;
	cor_file = ft_strsub(s_file, 0, ft_strlen(s_file) - index);
	temp = cor_file;
	cor_file = ft_strjoin(cor_file, "cor");
	ft_strdel(&temp);
	ft_strdel(&str);
	return (cor_file);
}

void			ft_write_file(char *file, t_operations *oper, char *str)
{
	char		*cor_file;
	int			fd;

	g_asm.instructions = (char*)malloc(g_asm.prog_size);
	cor_file = ft_prepare_for_writing(file);
	fd = open(cor_file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	(fd == -1) ? ft_exception("Can't open file.\n", 2) : 0;
	str = g_asm.instructions;
	ft_write_gen_info(fd);
	oper = g_asm.oper;
	while (oper)
	{
		ft_write_instructions(oper, &str);
		oper = oper->next;
	}
	if ((write(fd, g_asm.instructions, g_asm.prog_size)) >= 0)
	{
		ft_putstr("Writing output program to ");
		ft_putendl(cor_file);
	}
	else
		ft_exception("Can't write to file.\n", 2);
	ft_strdel(&cor_file);
	if (close(fd) < 0)
		ft_exception("Can't close file.\n", 2);
}
