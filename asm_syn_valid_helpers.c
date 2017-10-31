/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_syn_valid_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 22:24:26 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/29 22:24:27 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

void		ft_handle_err_desc_s_part(t_valid *valid, char **error_description)
{
	if ((valid->file[valid->l_num][valid->i]) == '"')
	{
		if (ft_handle_double_qoutes(valid, 1) == NULL)
			ft_exception("File is unnormed.", 2);
		valid->i += 1;
		(*error_description) = "STRING";
	}
	else if ((valid->file[valid->l_num][valid->i]) == LABEL_CHAR)
	{
		valid->i += 1;
		ft_label_reference(valid->file[valid->l_num] + valid->i, valid);
		(*error_description) = "INDIRECT_LABEL";
	}
	else if (DIRECT_CHARS(valid->file[valid->l_num], valid->i))
	{
		valid->i += 2;
		ft_label_reference(valid->file[valid->l_num] + valid->i, valid);
		(*error_description) = "DIRECT_LABEL";
	}
	else if (valid->file[valid->l_num][valid->i] == SEPARATOR_CHAR)
	{
		valid->i++;
		(*error_description) = "SEPARATOR";
	}
}

void		ft_handle_err_description(t_valid *valid, int flag)
{
	size_t		i;
	char		*temp;
	size_t		j;
	char		*error_description;

	i = valid->i;
	if (!ft_handle_err_desc_f_part(valid, &error_description))
		ft_handle_err_desc_s_part(valid, &error_description);
	temp = ft_strsub(valid->file[valid->l_num], i, valid->i - i);
	j = valid->i;
	valid->i = i;
	ft_crt_error(error_description, temp, valid, flag);
	valid->i = j;
	ft_strdel(&temp);
}

void		ft_syntax_error(t_valid *valid, char *error_description, int flag)
{
	if (error_description)
	{
		if (valid->errors == 0)
		{
			ft_putstr((flag) ? "Syntax error at ["
				: "Invalid instruction at [");
			ft_putnbr(valid->l_num + 1);
			ft_putchar(':');
			ft_putnbr(valid->i + 1);
			ft_putstr("] ");
			ft_putstr(error_description);
			ft_putchar('\n');
		}
	}
	else
	{
		ft_handle_err_description(valid, flag);
	}
	valid->errors += (error_description) ? 1 : 0;
}

void		ft_crt_error(char *str, char *temp, t_valid *valid, int flag)
{
	char		*string;
	char		*direct_str;

	string = "";
	string = ft_strjoin(string, str);
	direct_str = string;
	string = ft_strjoin(string, " \"");
	ft_memdel((void**)&direct_str);
	direct_str = string;
	string = ft_strjoin(string, temp);
	ft_memdel((void**)&direct_str);
	direct_str = string;
	string = ft_strjoin(string, "\"");
	ft_memdel((void**)&direct_str);
	direct_str = string;
	ft_syntax_error(valid, string, flag);
	ft_memdel((void**)&direct_str);
}

size_t		ft_is_gen_info_repeating(char *str, t_valid *valid)
{
	char		*temp;
	size_t		len;

	temp = ft_strsub(str, 0, ft_strlen((ft_strstr(str, NAME_CMD_STRING))
		? NAME_CMD_STRING : COMMENT_CMD_STRING));
	if (ft_strcmp(temp, NAME_CMD_STRING) == 0)
	{
		if (valid->name)
			ft_crt_error("COMMAND_NAME", temp, valid, 1);
		valid->name = 1;
	}
	else if (ft_strcmp(temp, COMMENT_CMD_STRING) == 0)
	{
		if (valid->cmmt)
			ft_crt_error("COMMAND_COMMENT", temp, valid, 1);
		valid->cmmt = 1;
	}
	len = ft_strlen(temp);
	ft_strdel(&temp);
	return (len);
}
