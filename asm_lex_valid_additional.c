/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_lex_valid_additional.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 22:20:39 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/29 22:20:40 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

void		ft_handle_label_declaration(char *str, t_valid *v)
{
	size_t		distance;
	char		*temp;

	temp = NULL;
	distance = ft_strlen(str);
	if (ft_strchr(str + v->i, LABEL_CHAR))
	{
		distance = ft_strchr(str, LABEL_CHAR) - str;
		temp = ft_strsub(str + v->i, 0, distance + 1);
	}
	if (ft_find_label_char(temp))
		ft_check_label_chars(str, distance, v);
	else
	{
		while (str[v->i] && str[v->i] != LABEL_CHAR)
		{
			if (!ft_strchr(LABEL_CHARS, str[v->i]))
				(POSS_CHRS(str, v->i)
				&& str[v->i + 1] != LABEL_CHAR) ? 0 : ft_lexical_err(v);
			v->i++;
		}
		if (str != NULL)
			v->i += (str[v->i] == '\0') ? 0 : 1;
	}
	(temp == NULL) ? 0 : ft_strdel(&temp);
}

void		ft_handle_label_invocation(char *str, t_valid *v)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (!ft_strchr(LABEL_CHARS, str[i])
			&& !(POSS_CHRS(str, i) && i != 0))
		{
			break ;
		}
		i++;
	}
	v->i += i;
	(i == 0) ? ft_lexical_err(v) : 0;
}

size_t		ft_skip_hex_digits(char *str)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			break ;
		i++;
	}
	return (i);
}

size_t		ft_handle_indirect(char *str, t_valid *v)
{
	if (str[v->i] == DIRECT_CHAR && ((str[v->i + 1] == '-'
		&& ft_isdigit(str[v->i + 2])) || ft_isdigit(str[v->i + 1])))
	{
		v->i += (str[v->i + 1] == '-') ? 2 : 1;
		v->i += ft_skip_hex_digits(str + v->i);
		return (1);
	}
	else if (str[v->i] == '-' && ft_isdigit(str[v->i + 1]))
	{
		v->i += 1;
		v->i += ft_skip_hex_digits(str + v->i);
		return (1);
	}
	else if (ft_isdigit(str[v->i]))
	{
		v->i += ft_skip_hex_digits(str + v->i);
		return (1);
	}
	else
	{
		return (0);
	}
}

void		ft_lex_handle_register(char *str, t_valid *v)
{
	while (str[v->i])
	{
		if (str[v->i] == '-' && !ft_isdigit(str[v->i + 1]))
		{
			if (!ft_handle_indirect(str + v->i, v))
				ft_lexical_err(v);
		}
		else if ((str[v->i] == ' ' || str[v->i] == '\t')
			&& str[v->i - 1] == '-')
			ft_lexical_err(v);
		v->i++;
	}
}
