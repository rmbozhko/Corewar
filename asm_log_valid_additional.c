/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_log_valid_additional.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 22:21:13 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/29 22:21:14 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

int			ft_check_each_arg(int argument, int found_num, int seq_num)
{
	int		arg_type;

	arg_type = g_op_tab[found_num].args[0][seq_num];
	if (arg_type == 1 && argument == 1)
		return (1);
	else if (arg_type == 2 && argument == 2)
		return (1);
	else if (arg_type == 3 && (argument == 2 || argument == 1))
		return (1);
	else if (arg_type == 4 && (argument == 3))
		return (1);
	else if (arg_type == 5 && (argument == 3 || argument == 1))
		return (1);
	else if (arg_type == 6 && (argument == 3 || argument == 2))
		return (1);
	else if (arg_type == 7 && (argument == 3 || argument == 2 || argument == 1))
		return (1);
	else
		return (0);
}

size_t		ft_get_arg_type(char *str)
{
	if (str[0] == 'r' && ft_isdigit(str[1]))
		return (REG_CODE);
	else if ((str[0] == DIRECT_CHAR && str[1] == LABEL_CHAR)
			|| (str[0] == DIRECT_CHAR && (ft_isdigit(str[1])
			|| (str[1] == '-' && ft_isdigit(str[2])))))
		return (DIR_CODE);
	else if ((str[0] == '-' && ft_isdigit(str[1]))
			|| ft_isdigit(str[0]) || str[0] == LABEL_CHAR)
		return (IND_CODE);
	else
		return (0);
}

size_t		ft_handle_argument(char *str, int cmd_opcode, size_t arg_num)
{
	int			i;
	size_t		arg_type;

	i = 0;
	arg_type = ft_get_arg_type(str);
	if (i >= g_op_tab[cmd_opcode].count_args)
	{
		ft_log_error(i, arg_type, cmd_opcode, 1);
	}
	else if (arg_type)
	{
		if (ft_check_each_arg(arg_type, cmd_opcode, arg_num))
			return (8);
	}
	return (arg_type);
}

size_t		ft_validate_args(char **commands, int cmd_opcode)
{
	size_t		i;
	char		*str;
	size_t		arg_type;

	i = 0;
	str = ft_strnew(0);
	while (commands[i])
	{
		ft_strdel(&str);
		str = ft_strip(commands[i]);
		if ((arg_type = ft_handle_argument(str, cmd_opcode, i)) != 8)
		{
			ft_strdel(&str);
			ft_log_error(i, arg_type, cmd_opcode, 0);
			return (0);
		}
		i++;
	}
	ft_strdel(&str);
	return (1);
}

char		*ft_get_mltl_string(size_t i, size_t j, t_valid *valid)
{
	char		*temp;
	char		*str;
	char		*string;

	temp = ft_strnew(0);
	string = temp;
	while (j < valid->l_num && valid->file[j] != NULL)
	{
		temp = ft_strjoin(temp, ft_strdup(valid->file[j]) + i);
		ft_strdel(&string);
		string = temp;
		i = 0;
		j++;
	}
	str = ft_strsub(valid->file[j], i, valid->i - i);
	temp = ft_strjoin(temp, str);
	ft_strdel(&string);
	ft_strdel(&str);
	return (temp);
}
