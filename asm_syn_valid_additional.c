/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_syn_valid_additional.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 22:24:15 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/29 22:24:16 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

char		*ft_syn_dot(char *str, t_valid *valid, int double_qoute_counter)
{
	valid->i += ft_is_gen_info_repeating(str, valid);
	while (str[valid->i])
	{
		if (str[valid->i] == '"' && double_qoute_counter == 0)
		{
			if ((str = ft_handle_double_qoutes(valid, 1)) == NULL)
				break ;
			double_qoute_counter = 1;
		}
		else if (str[valid->i] == COMMENT_CHAR
			|| str[valid->i] == COMMENT_CHAR2)
		{
			if (double_qoute_counter != 1)
				ft_syntax_error(valid, "ENDLINE", 1);
			break ;
		}
		else if (str[valid->i] != ' ' && str[valid->i] != '\t')
			ft_syntax_error(valid, NULL, 1);
		valid->i++;
	}
	ft_strdel(&str);
	return (str);
}

size_t		ft_syn_reg(t_valid *valid, char *str)
{
	size_t		i;
	size_t		num_counter;
	char		*temp;

	temp = NULL;
	num_counter = 1;
	while (str[valid->i])
	{
		if (!ft_isdigit(str[valid->i]))
			break ;
		else
			num_counter++;
		valid->i++;
	}
	temp = ft_strsub(str, 0, num_counter - 1);
	i = ft_atoi(temp);
	ft_strdel(&temp);
	return (i > REG_NUMBER) ? (0) : (1);
}

size_t		ft_is_valid_param(t_valid *valid, char *str)
{
	if (str[valid->i] == 'r'
		&& (str[valid->i - 1] == ' ' || str[valid->i - 1] == '\t'
		|| str[valid->i - 1] == SEPARATOR_CHAR)
		&& ft_isdigit(str[valid->i + 1]))
	{
		valid->i++;
		return (ft_syn_reg(valid, str));
	}
	else if (DIRECT_CHARS(str, valid->i) || (str[valid->i] == LABEL_CHAR))
	{
		valid->i += (str[valid->i] == LABEL_CHAR) ? 1 : 2;
		return (ft_label_reference(str + valid->i, valid));
	}
	else if ((str[valid->i] == '-' && ft_isdigit(str[valid->i + 1]))
		|| ft_isdigit(str[valid->i]) || str[valid->i] == DIRECT_CHAR)
		return (ft_handle_indirect(str, valid));
	else if (str[valid->i] == 'r' &&
			(str[valid->i - 1] != ' ' && str[valid->i - 1] != '\t'))
		return (2);
	else
		return (0);
}

size_t		ft_to_separator(t_valid *valid)
{
	while (valid->file[valid->l_num][valid->i])
	{
		if (NOT_SPACES)
		{
			if (valid->file[valid->l_num][valid->i] == SEPARATOR_CHAR
					|| CMMT(valid->file, valid->l_num, valid->i))
				break ;
			else
				ft_syntax_error(valid, NULL, 1);
		}
		valid->i++;
	}
	if (valid->file[valid->l_num][valid->i] == SEPARATOR_CHAR)
	{
		if (valid->file[valid->l_num][valid->i + 1] == '\0' ||
			ft_space_based_line(valid->file[valid->l_num] + (valid->i + 1)))
			ft_syntax_error(valid, "ENDLINE", 1);
		else
			return (1);
	}
	return (0);
}

void		ft_handle_instr_invoke(char *str, t_valid *valid)
{
	size_t		i;

	valid->flag = 1;
	while (str[valid->i] && valid->flag)
	{
		if ((i = ft_is_valid_param(valid, str)) && valid->flag)
		{
			valid->flag = ft_to_separator(valid);
			if (valid->flag == 0)
				break ;
		}
		else if (str[valid->i] != ' ' && str[valid->i] != '\t')
		{
			if (str[valid->i] == COMMENT_CHAR || str[valid->i] == COMMENT_CHAR2)
				break ;
			ft_syntax_error(valid, NULL, 1);
		}
		if (i == 2)
			break ;
		valid->i += (str[valid->i] != '\0') ? 1 : 0;
	}
}
