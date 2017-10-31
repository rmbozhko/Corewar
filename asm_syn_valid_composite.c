/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_syn_valid_composite.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 22:23:32 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/29 22:23:58 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

size_t		ft_label_reference(char *str, t_valid *valid)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (!ft_strchr(LABEL_CHARS, str[i]))
			break ;
		i++;
	}
	valid->i += i;
	return ((i > 0) ? 1 : 0);
}

size_t		ft_handle_err_desc_f_part(t_valid *valid, char **error_description)
{
	if (ft_space_based_line(CURR_STRING))
		(*error_description) = "ENDLINE";
	else if (CURR_ELEM == 'r' &&
		ft_isdigit(valid->file[valid->l_num][valid->i + 1]))
	{
		valid->i++;
		(*error_description) = (ft_syn_reg(valid, valid->file[valid->l_num]))
		? "REGISTER" : "INSTRUCTION";
	}
	else if ((CURR_ELEM == '-'
		&& ft_isdigit(valid->file[valid->l_num][valid->i + 1]))
		|| ft_isdigit(CURR_ELEM) || CURR_ELEM == DIRECT_CHAR)
	{
		(*error_description) = (CURR_ELEM == DIRECT_CHAR)
		? "DIRECT" : "INDIRECT";
		ft_handle_indirect(valid->file[valid->l_num], valid);
	}
	else if (ft_strchr(LABEL_CHARS, CURR_ELEM))
	{
		ft_label_reference(CURR_STRING, valid);
		(*error_description) = "INSTRUCTION";
	}
	else
		return (0);
	return (1);
}

size_t		ft_count_prog_len(void)
{
	t_operations		*oper;
	size_t				instr_summ;

	instr_summ = 0;
	oper = g_asm.oper;
	while (oper)
	{
		instr_summ += oper->instr_len;
		oper = oper->next;
	}
	return (instr_summ);
}

size_t		ft_reveal_label_declaration_addr(size_t pos)
{
	size_t				addr;
	t_operations		*oper;
	size_t				i;

	i = 0;
	addr = i;
	oper = g_asm.oper;
	while (i < pos)
	{
		addr += oper->instr_len;
		i++;
		oper = oper->next;
	}
	return (addr);
}

size_t		ft_get_label_addr(char *str)
{
	t_labels			*label;

	label = g_asm.label;
	while (label)
	{
		if (!ft_strcmp(label->name, str))
			return (ft_reveal_label_declaration_addr(label->f_key));
		label = label->next;
	}
	return (0);
}
