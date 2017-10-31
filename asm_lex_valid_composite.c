/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_lex_valid_composite.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 22:20:25 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/29 22:20:27 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

size_t		ft_till_is_word(char *str)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == DIRECT_CHAR
			|| str[i] == LABEL_CHAR || (str[i] == '-'
			&& ft_isdigit(str[i + 1])))
			break ;
		i++;
	}
	return (i);
}

int			compare_command(char *str)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		if (ft_strcmp(str, g_op_tab[i].command_name) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int			ft_handle_post_cmd_str(int found_num, char *str, size_t i)
{
	found_num = (size_t)found_num;
	if ((str[i] == DIRECT_CHAR && str[i + 1] == LABEL_CHAR))
		return (0);
	else if (str[i] == ' ' || str[i] == '\t' || str[i] == SEPARATOR_CHAR)
		return (0);
	else if (str[i] != 'i')
		return (1);
	return (0);
}

int			ft_is_command(char *str, t_valid *v, size_t i)
{
	char		*cropped;
	int			found_num;
	int			found_i;

	found_num = -1;
	while (str[i])
	{
		cropped = ft_strsub(str, ft_skip_whitespaces(str, 0), i);
		if (compare_command(cropped) >= 0)
		{
			found_num = compare_command(cropped);
			found_i = i;
		}
		ft_strdel(&cropped);
		i++;
	}
	if (found_num == -1)
		return (-1);
	if (ft_handle_post_cmd_str(found_num, str, found_i))
		return (-1);
	v->i += ft_skip_whitespaces(str, 0);
	return (found_num);
}

void		ft_check_label_chars(char *str, size_t end, t_valid *v)
{
	size_t		i;

	i = 0;
	while (i < end && str[i])
	{
		if (!ft_strchr(LABEL_CHARS, str[i]))
			break ;
		i++;
	}
	v->i += i;
}
