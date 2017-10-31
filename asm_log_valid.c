/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 19:31:32 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/31 18:46:07 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

void					ft_log_handle_dot(t_valid *valid)
{
	char		*temp;
	size_t		i;
	size_t		j;

	temp = ft_strsub(valid->file[valid->l_num], 0,
			ft_strlen(NAME_CMD_STRING));
	valid->i += ft_strlen((ft_strcmp(temp, NAME_CMD_STRING) == 0)
			? NAME_CMD_STRING : COMMENT_CMD_STRING);
	valid->i = ft_skip_whitespaces(valid->file[valid->l_num], valid->i);
	i = valid->i + 1;
	j = valid->l_num;
	ft_handle_double_qoutes(valid, 1);
	if (ft_strcmp(temp, NAME_CMD_STRING) == 0)
		g_asm.name = ft_get_mltl_string(i, j, valid);
	else
		g_asm.cmmt = ft_get_mltl_string(i, j, valid);
	ft_strdel(&temp);
	valid->i += ft_strlen(valid->file[valid->l_num] + valid->i);
}

int						ft_count_args(t_valid *valid)
{
	size_t		commas;

	commas = 0;
	while (valid->file[valid->l_num][valid->i])
	{
		if (CMMT(valid->file, valid->l_num, valid->i))
			break ;
		else if (valid->file[valid->l_num][valid->i] == SEPARATOR_CHAR)
			commas++;
		valid->i++;
	}
	return (commas + 1);
}

t_operations			*ft_log_handle_command(t_valid *valid, size_t j)
{
	int					cmd_opcode;
	char				**cmds;
	t_operations		*oper;
	char				*str;

	valid->i = ft_skip_whitespaces(valid->file[valid->l_num], valid->i);
	cmd_opcode = ft_is_command(CURR_STRING, valid, 0);
	valid->i = ft_skip_whitespaces(valid->file[valid->l_num],
		valid->i + ft_strlen(g_op_tab[cmd_opcode].command_name));
	j = valid->i;
	oper = NULL;
	cmds = NULL;
	if (ft_count_args(valid) < g_op_tab[cmd_opcode].count_args)
		ft_log_error(0, 0, cmd_opcode, 1);
	else
	{
		str = ft_validate_string(valid->file[valid->l_num] + j);
		cmds = ft_strsplit(str, SEPARATOR_CHAR);
		if (ft_validate_args(cmds, cmd_opcode))
			oper = ft_create_command(cmd_opcode, cmds);
		ft_strdel(&str);
	}
	ft_free_bidarr(cmds, ft_bidlen(cmds));
	valid->i += ft_strlen(valid->file[valid->l_num] + valid->i);
	return (oper);
}

void					ft_log_handle_label(t_valid *valid)
{
	char				*temp;
	t_operations		*oper;
	t_labels			*label;
	size_t				i;

	temp = NULL;
	i = valid->i;
	if (ft_is_label(valid, 0))
	{
		temp = ft_strsub(valid->file[valid->l_num], i, valid->i - 1);
		if (!ft_space_based_line(valid->file[valid->l_num] + valid->i))
			oper = ft_log_handle_command(valid, 0);
		else
		{
			valid->l_num += (valid->file[valid->l_num + 1]) ? 1 : 0;
			valid->i = (valid->file[valid->l_num + 1]) ? 0 : valid->i;
			oper = (valid->file[valid->l_num] != NULL)
				? ft_get_command(valid, 0, valid->l_num) : NULL;
		}
		label = ft_create_label(temp, g_asm.instr_counter);
		ft_strdel(&temp);
		ft_add_cmd_to_label_list(label);
		(oper != NULL) ? ft_add_cmd_to_list(oper) : 0;
	}
}

void					ft_logical_validation(t_valid *valid)
{
	t_operations		*oper;

	while (valid->file[valid->l_num])
	{
		valid->i = ft_skip_whitespaces(valid->file[valid->l_num], 0);
		while (valid->file[valid->l_num][valid->i])
		{
			if (GEN_INFO_STR)
				ft_log_handle_dot(valid);
			else if (ft_is_command(CURR_STRING, valid, 0) != -1)
			{
				if ((oper = ft_log_handle_command(valid, 0)) != NULL)
					ft_add_cmd_to_list(oper);
			}
			else if (ft_strchr(LABEL_CHARS, CURR_ELEM))
				ft_log_handle_label(valid);
			else if (CMMT(valid->file, valid->l_num, valid->i)
					|| valid->l_num == ft_bidlen(valid->file))
				break ;
			valid->i += (CURR_ELEM != '\0') ? 1 : 0;
		}
		valid->l_num += (valid->l_num != ft_bidlen(valid->file)) ? 1 : 0;
	}
	ft_check_label_appear(valid->file, valid);
}
