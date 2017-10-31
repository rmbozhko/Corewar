/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gathering.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 17:04:13 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/29 17:41:58 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

t_labels				*ft_create_label(char *str, size_t key)
{
	t_labels		*label;

	label = (t_labels*)malloc(sizeof(t_labels));
	label->name = ft_strdup(str);
	label->f_key = key;
	label->next = NULL;
	return (label);
}

static	char			*ft_extract_value(char *arg)
{
	char			*temp;

	temp = NULL;
	if (arg[0] == 'r' && ft_isdigit(arg[1]))
	{
		temp = ft_strsub(arg, 1, ft_strlen(arg + 1));
	}
	else if ((arg[0] == '-' && ft_isdigit(arg[1]))
			|| ft_isdigit(arg[0]) || (arg[0] == DIRECT_CHAR))
	{
		temp = ft_strsub(arg, ((arg[0] == DIRECT_CHAR) ? 1 : 0),
				ft_strlen(arg + ((arg[0] == DIRECT_CHAR) ? 1 : 0)));
	}
	return (temp);
}

size_t					ft_get_label_size(size_t cmd_opcode)
{
	if ((cmd_opcode == 0) || (cmd_opcode == 1)
		|| (cmd_opcode >= 5 && cmd_opcode <= 7)
		|| (cmd_opcode == 12))
		return (4);
	else if ((cmd_opcode >= 8 && cmd_opcode <= 11)
		|| (cmd_opcode == 13) || (cmd_opcode == 14))
		return (2);
	else
		return (0);
}

t_arg					*ft_create_arg(char *arg, size_t flag)
{
	t_arg		*argument;

	argument = (t_arg*)malloc(sizeof(t_arg));
	if (flag)
	{
		argument->type = ft_get_arg_type(arg);
		if (DIRECT_CHARS(arg, 0) || (arg[0] == LABEL_CHAR))
		{
			arg += ((arg[0] == LABEL_CHAR) ? 1 : 2);
			argument->label = ft_strdup(arg);
			argument->value = NULL;
		}
		else
		{
			argument->value = ft_extract_value(arg);
			argument->label = NULL;
		}
	}
	else
	{
		argument->type = 0;
		argument->value = NULL;
		argument->label = NULL;
	}
	return (argument);
}

t_operations			*ft_create_command(size_t cmd_opcode, char **arguments)
{
	t_operations		*oper;
	size_t				i;
	char				*temp;

	i = 0;
	oper = (t_operations*)malloc(sizeof(t_operations));
	oper->command = cmd_opcode;
	oper->args = (t_arg**)malloc(sizeof(t_arg*) * ARG_MAX_NUM + 1);
	while (i < ARG_MAX_NUM)
	{
		if (i < ft_bidlen(arguments))
		{
			temp = ft_strip(arguments[i]);
			oper->args[i] = ft_create_arg(temp, 1);
			ft_strdel(&temp);
		}
		else if (i >= ft_bidlen(arguments))
			oper->args[i] = ft_create_arg(temp, 0);
		i++;
	}
	oper->args[i] = NULL;
	oper->cod_byte = ft_get_cod_byte(oper);
	oper->instr_len = ft_count_instr_len(oper);
	oper->next = NULL;
	return (oper);
}
