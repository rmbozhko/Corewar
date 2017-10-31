/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 20:13:37 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/29 21:24:17 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

void		ft_syn_handle_instr(char *str, t_valid *valid)
{
	size_t		i;

	i = valid->i;
	while (str[valid->i])
	{
		if (!ft_strchr(LABEL_CHARS, str[valid->i]))
			break ;
		valid->i++;
	}
	if (str[valid->i] != '\0')
	{
		ft_handle_instr_invoke(valid->file[valid->l_num], valid);
		valid->i = i;
		ft_syntax_error(valid, NULL, 0);
		valid->i += ft_strlen(valid->file[valid->l_num] + valid->i);
	}
	else if (ft_space_based_line(str + valid->i) || str[valid->i] == '\0')
	{
		valid->i = i;
		ft_syntax_error(valid, NULL, 1);
	}
}

void		ft_syn_label(t_valid *valid)
{
	int			cmd_num;

	cmd_num = 1;
	while (valid->file[valid->l_num][valid->i])
	{
		if ((cmd_num = ft_is_command(CURR_STRING, valid, 0)) != -1)
		{
			valid->i += ft_strlen(g_op_tab[cmd_num].command_name);
			ft_handle_instr_invoke(valid->file[valid->l_num], valid);
		}
		else if (ft_strchr(LABEL_CHARS, valid->file[valid->l_num][valid->i]))
			ft_syn_handle_instr(valid->file[valid->l_num], valid);
		else if (CMMT(valid->file, valid->l_num, valid->i))
			break ;
		else
		{
			(NOT_SPACES) ? ft_syntax_error(valid, NULL, 1) : 0;
			valid->i += (valid->file[valid->l_num][valid->i]) ? 1 : 0;
		}
	}
}

size_t		ft_is_label(t_valid *valid, size_t i)
{
	i = valid->i;
	while (valid->file[valid->l_num][valid->i])
	{
		if ((CURR_ELEM != LABEL_CHAR && !ft_strchr(LABEL_CHARS, CURR_ELEM))
			|| (CURR_ELEM == LABEL_CHAR && valid->i == i))
		{
			valid->i = i;
			return (0);
		}
		else if (valid->file[valid->l_num][valid->i] == LABEL_CHAR)
			break ;
		valid->i++;
	}
	if (valid->file[valid->l_num][valid->i] == LABEL_CHAR)
	{
		valid->flag = 0;
		valid->i++;
		return (1);
	}
	else
	{
		valid->i = i;
		return (0);
	}
}

void		ft_check_main_body(t_valid *valid, int cmd)
{
	while (valid->file[valid->l_num][valid->i])
	{
		if (GEN_INFO_STR)
		{
			if (!ft_syn_dot(CURR_STRING, valid, 0))
				break ;
		}
		else if (((cmd = ft_is_command(CURR_STRING, valid, 0)) != -1)
			&& GEN_INFO)
		{
			valid->i += ft_strlen(g_op_tab[cmd].command_name);
			ft_handle_instr_invoke(valid->file[valid->l_num], valid);
		}
		else if (ft_is_label(valid, 0) && GEN_INFO)
			(!ft_space_based_line(CURR_STRING)) ? ft_syn_label(valid) : 0;
		else if (ft_strchr(LABEL_CHARS, CURR_ELEM) && GEN_INFO)
			ft_syn_handle_instr(valid->file[valid->l_num], valid);
		else if (CMMT(valid->file, valid->l_num, valid->i))
			break ;
		else
		{
			(NOT_SPACES) ? ft_syntax_error(valid, NULL, 1) : 0;
			valid->i += (CURR_ELEM != '\0') ? 1 : 0;
		}
	}
}

void		ft_syntax_validation(t_valid *valid)
{
	valid->i = 0;
	valid->l_num = 0;
	while (valid->file[valid->l_num])
	{
		valid->i = ft_skip_whitespaces(valid->file[valid->l_num], 0);
		ft_check_main_body(valid, -1);
		valid->l_num += (valid->file[valid->l_num] == NULL) ? 0 : 1;
	}
	if ((valid->flag) && (!valid->errors))
		ft_syntax_error(valid, "END \"(null)\"", 1);
	if (!ft_space_based_line(valid->file[ft_bidlen(valid->file) - 2])
			&& (!valid->errors))
	{
		valid->errors++;
		ft_putstr("Syntax error - unexpected end of input \
			(Perhaps you forgot to end with a newline ?)\n");
	}
}
