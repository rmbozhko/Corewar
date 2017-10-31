/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_lex_valid_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 22:21:01 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/29 22:21:02 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

int			ft_space_based_line(char *str)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

size_t		ft_skip_chars(char *str, int (*f)(int), int c)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (c != -1 && f == NULL)
		{
			if (str[i] != c)
				break ;
		}
		else if (c == -1 && f != NULL)
		{
			if (!f(str[i]))
				break ;
		}
		i++;
	}
	return (i);
}

char		*ft_handle_double_qoutes(t_valid *v, int db_quote_flag)
{
	char		*temp;
	size_t		i;

	temp = ft_strsub(v->file[v->l_num], v->i + 1, ft_strlen(v->file[v->l_num]));
	while (v->file[v->l_num] && !(i = 0))
	{
		while (temp[i] && db_quote_flag)
		{
			db_quote_flag = (temp[i] == '"') ? 0 : db_quote_flag;
			i++;
		}
		if (!db_quote_flag)
			break ;
		if (temp[i] == '\0')
		{
			v->l_num++;
			v->i = (db_quote_flag) ? 0 : v->i;
		}
		ft_strdel(&temp);
		temp = (v->file[v->l_num]) ? ft_strdup(v->file[v->l_num]) : temp;
	}
	v->i += i;
	((v->file[v->l_num] == NULL) && temp != NULL) ? ft_strdel(&temp) : 0;
	((temp[i] == '\0') && temp != NULL) ? ft_strdel(&temp) : 0;
	return (temp);
}

size_t		ft_name_cmmt(char *line, int flag, t_valid *v)
{
	char		*str;
	size_t		i;

	str = ft_strsub(line, 0, ft_strlen((flag)
				? NAME_CMD_STRING : COMMENT_CMD_STRING));
	i = ft_strlen(str);
	if (ft_strcmp(((flag) ? NAME_CMD_STRING : COMMENT_CMD_STRING), str) == 0)
		i = ft_strlen((flag) ? NAME_CMD_STRING : COMMENT_CMD_STRING);
	else
		ft_lexical_err(v);
	ft_strdel(&str);
	return (i);
}

void		ft_handle_dot(char *str, t_valid *v)
{
	size_t		i;

	i = 1;
	if (ft_strstr(str, NAME_CMD_STRING))
	{
		i = ft_name_cmmt(str, 1, v);
	}
	else if (ft_strstr(str, COMMENT_CMD_STRING))
	{
		i = ft_name_cmmt(str, 0, v);
	}
	else
	{
		ft_lexical_err(v);
	}
	v->i += i;
}
