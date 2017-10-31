/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 20:38:53 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/29 21:32:45 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include <stdio.h>

int			ft_find_label_char_f_part(char *temp)
{
	char		*str;

	str = ft_strchr(temp, LABEL_CHAR);
	if (ft_strchr(temp, COMMENT_CHAR))
	{
		if (str != NULL)
		{
			if (str - ft_strchr(temp, COMMENT_CHAR) < 0)
				return (1);
		}
	}
	else if (ft_strchr(temp, '"'))
	{
		if (str != NULL)
		{
			if (str - ft_strchr(temp, '"') < 0)
				return (1);
		}
	}
	return (0);
}

int			ft_find_label_char(char *temp)
{
	char		*str;
	int			status;

	str = ft_strchr(temp, LABEL_CHAR);
	if (!(status = ft_find_label_char_f_part(temp)))
	{
		if (ft_strchr(temp, COMMENT_CHAR2))
		{
			if (str != NULL)
			{
				if (str - ft_strchr(temp, COMMENT_CHAR2) < 0)
					status = 1;
			}
		}
		else if (ft_strchr(temp, DIRECT_CHAR))
		{
			if (str != NULL)
			{
				if ((str - ft_strchr(temp, DIRECT_CHAR)) > 0)
					status = 1;
			}
		}
	}
	return (status);
}

size_t		ft_check_str_chars_f_part(char *str, t_valid *v)
{
	int		command_id;

	if (str[v->i] == NAME_CMD_STRING[0]
		|| str[v->i] == COMMENT_CMD_STRING[0])
		ft_handle_dot(str + v->i, v);
	else if (str[v->i] == COMMENT_CHAR || str[v->i] == COMMENT_CHAR2)
		v->i += ft_strlen(str + v->i);
	else if ((command_id = ft_is_command(str + v->i, v, 0)) != -1)
		v->i += ft_strlen(g_op_tab[command_id].command_name);
	else if (DIRECT_CHARS(str, v->i))
	{
		v->i += 2;
		ft_handle_label_invocation(str + v->i, v);
	}
	else
		return (0);
	return (1);
}

void		ft_check_str_chars(char *str, t_valid *v, int command_id)
{
	if (str[v->i] == NAME_CMD_STRING[0]
		|| str[v->i] == COMMENT_CMD_STRING[0])
	{
		ft_handle_dot(str + v->i, v);
	}
	else if (str[v->i] == COMMENT_CHAR || str[v->i] == COMMENT_CHAR2)
		v->i += ft_strlen(str + v->i);
	else if (str[v->i] == '"')
	{
		v->i++;
		if ((str = ft_handle_double_qoutes(v, 1)) == NULL)
			return ;
		v->i += 1;
	}
	else if ((command_id = ft_is_command(str + v->i, v, 0)) != -1)
		v->i += ft_strlen(g_op_tab[command_id].command_name);
	else if (DIRECT_CHARS(str, v->i))
	{
		v->i += 2;
		ft_handle_label_invocation(str + v->i, v);
	}
	else
		ft_check_str_chars_add(str, v);
	(str[v->i] != '\0' && v->file[v->l_num])
		? ft_check_str_chars(str, v, 0) : 0;
}

void		ft_lexical_validation(t_valid *v)
{
	while (v->file[v->l_num])
	{
		v->i = ft_skip_whitespaces(v->file[v->l_num], 0);
		if (v->file[v->l_num][v->i] != COMMENT_CHAR
			&& v->file[v->l_num][v->i] != COMMENT_CHAR2
			&& !ft_space_based_line(v->file[v->l_num] + v->i))
			ft_check_str_chars(v->file[v->l_num], v, 0);
		v->l_num += (v->file[v->l_num] == NULL) ? 0 : 1;
	}
}
