/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_gather_additional.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 19:25:44 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/31 16:29:28 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

void					ft_check_str_chars_add(char *str, t_valid *v)
{
	if (str[v->i] == 'r')
		v->i += ft_skip_chars(str + v->i, NULL, 'r');
	else if ((str[v->i] == '-' && ft_isdigit(str[v->i + 1]))
		|| ft_isdigit(str[v->i]) || (str[v->i] == DIRECT_CHAR))
		(!ft_handle_indirect(str, v)) ? ft_lexical_err(v) : 0;
	else if (str[v->i] == LABEL_CHAR || ft_strchr(LABEL_CHARS, str[v->i]))
	{
		(str[v->i] == LABEL_CHAR)
		? ft_handle_label_invocation(str + (++v->i), v)
		: ft_handle_label_declaration(str, v);
	}
	else if (str[v->i] == SEPARATOR_CHAR)
		v->i += ft_skip_chars(str + v->i, NULL, SEPARATOR_CHAR);
	else
	{
		(str[v->i] != ' ' && str[v->i] != '\t')
			? ft_lexical_err(v) : v->i++;
	}
}

t_operations			*ft_get_command(t_valid *valid, size_t i, size_t j)
{
	while (valid->file[valid->l_num])
	{
		valid->i = ft_skip_whitespaces(valid->file[valid->l_num], valid->i);
		while (valid->file[valid->l_num][valid->i])
		{
			i = valid->i;
			if (CMMT(valid->file, valid->l_num, valid->i))
				break ;
			else if (ft_is_command(CURR_STRING, valid, 0) != -1)
				return (ft_log_handle_command(valid, 0));
			else if (ft_is_label(valid, 0))
			{
				valid->l_num = j;
				valid->i = i - 1;
				return (NULL);
			}
			valid->i++;
		}
		valid->l_num++;
	}
	valid->i = 0;
	valid->l_num = j + 1;
	return (NULL);
}

void					ft_gen_info_errors_handling(t_valid *valid)
{
	if (ft_strlen(g_asm.name) > PROG_NAME_LENGTH)
	{
		ft_putendl("Champion name too long (Max length ");
		ft_putnbr(PROG_NAME_LENGTH);
		ft_putendl(")");
		valid->errors++;
	}
	if (ft_strlen(g_asm.cmmt) > COMMENT_LENGTH)
	{
		ft_putstr("Champion comment too long (Max length ");
		ft_putnbr(COMMENT_LENGTH);
		ft_putendl(")");
		valid->errors++;
	}
}

unsigned char			ft_get_cod_byte(t_operations *oper)
{
	t_arg				**arg;
	unsigned char		c;
	size_t				i;

	i = 0;
	if (oper->command == 0 || oper->command == 8
		|| oper->command == 11 || oper->command == 14)
		return (0);
	else
	{
		c = 0;
		arg = oper->args;
		while (i < ARG_MAX_NUM)
		{
			(arg[i]->type != 0) ? c |= arg[i]->type : 0;
			c <<= 2;
			i++;
		}
		return (c);
	}
}

size_t					ft_count_instr_len(t_operations *oper)
{
	size_t		len;
	t_arg		**args;
	size_t		i;

	i = 0;
	len = 1;
	len += (oper->cod_byte != 0) ? 1 : 0;
	args = oper->args;
	while (i < ARG_MAX_NUM)
	{
		if (args[i]->type != 0)
		{
			if (args[i]->type == DIR_CODE)
				len += ft_get_label_size(oper->command);
			else if (args[i]->type == REG_CODE)
				len += 1;
			else if (args[i]->type == IND_CODE)
				len += 2;
		}
		i++;
	}
	return (len);
}
