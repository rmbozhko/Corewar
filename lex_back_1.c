#include "asm.h"
#include "op.h"

int 		ft_spaces_based_line(char *str)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

size_t		ft_skip_chars(char *str, int(*f)(int), int c)
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

char 		*ft_handle_double_qoutes(t_valid *valid)
{
	char 		*temp;
	size_t		i;
	int 		db_quote_flag;

	db_quote_flag = 1;
	temp = ft_strsub(valid->file[valid->line_num], valid->i + 1, ft_strlen(valid->file[valid->line_num]));
	printf("temp_string:%s\n", temp);
	while (valid->file[valid->line_num])
	{
		i = 0;
		while (temp[i] && db_quote_flag)
		{
			db_quote_flag = (temp[i] == '"') ? 0 : db_quote_flag;
			// if (temp[i] == COMMENT_CHAR || temp[i] == COMMENT_CHAR2)
				// break ;
			i++;
		}
		if (!db_quote_flag)
			break ;
		ft_memdel((void**)&temp);
		valid->line_num++;
		temp = (valid->file[valid->line_num]) ? ft_strdup(valid->file[valid->line_num]) : temp;
	}
	valid->i += i;//(temp[i] == '\0') ? ft_strlen() : i - 1;
	printf("INDEX:%zu\n", valid->i);
	return ((temp[i] == '\0') ? NULL : temp);
}

size_t 		ft_name_cmmt(char *line, int flag, t_valid *valid)
{
	char		*str;
	size_t		i;

	str = ft_strsub(line, 0, ft_strlen((flag) ? NAME_CMD_STRING : COMMENT_CMD_STRING));
	i = ft_strlen(str);
	if (ft_strcmp(((flag) ? NAME_CMD_STRING : COMMENT_CMD_STRING), str) == 0)
	{
		i = ft_strlen((flag) ? NAME_CMD_STRING : COMMENT_CMD_STRING);
		// printf("HERE!\n");
		// while (line[i])
		// {
		// 	if (line[i] == '"')
		// 	{
		// 		if ((line = ft_handle_double_qoutes(valid)) == NULL)
		// 			break ;
		// 	}
		// 	else if (line[i] == COMMENT_CHAR || line[i] == COMMENT_CHAR2)
		// 		break ;
		// 	else if (!ft_strchr(LABEL_CHARS, line[i]) && line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != SEPARATOR_CHAR)
		// 	{
		// 		ft_lexical_err(valid);
		// 	}
		// 	i++;
		// }
	}
	else
		ft_lexical_err(valid);
	return (i);
	ft_memdel((void**)&str);
}

size_t 		ft_handle_dot(char *str, t_valid* valid)
{
	size_t		i;

	i = 1;
	if (ft_strstr(str, NAME_CMD_STRING))
	{
		i = ft_name_cmmt(str, 1, valid);
	}
	else if (ft_strstr(str, COMMENT_CMD_STRING))
	{
		i = ft_name_cmmt(str, 0, valid);
	}
	else
		ft_lexical_err(valid);
	printf("INDEX OF THE STRING_________:%zu | %s\n", i, str + i);
	return (i);
}

int			ft_is_command(char *str)
{
	int			i;
	char 		*temp;
	char 		*string;//

	string = ft_lstrip(str); //
	i = -1;
	while (op_tab[++i].count_args != 0)
	{
		if (ft_strlen(string) >= ft_strlen(op_tab[i].command_name)) // str instead string
			temp = ft_strsub(string, 0, ft_strlen(op_tab[i].command_name)); // str instead string
		else
			continue ;
		if (ft_strcmp(temp, op_tab[i].command_name) == 0)
		{
			ft_memdel((void**)&string);
			return (i);
		}
		ft_memdel((void**)&temp);
	}
	return (-1);
}

size_t		ft_check_label_chars(char *str, size_t end, t_valid *valid)
{
	size_t		i;

	i = 0;
	printf("%s | %zu | %zu\n",str, end, valid->i);
	while (i < end && str[i])
	{
		if (str[i] == '"')
		{
			printf("%s | %zu | %zu\n",str + i, end, valid->i);
			if ((str = ft_handle_double_qoutes(valid)) == NULL)
				break ;
		}
		else if (str[i] == COMMENT_CHAR2 || str[i] == COMMENT_CHAR)
			break ;
		else if (!ft_strchr(LABEL_CHARS, str[i]) && str[i] != SEPARATOR_CHAR && str[i] != ' ' && str[i] != '\t')
		{
			ft_lexical_err(valid);
		}
		i++;
	}
	valid->i += (str[i] != '\0' && str[i] != COMMENT_CHAR2 && str[i] != COMMENT_CHAR) ? i : ft_strlen(str) - 1;
	return (i);
}

void 		ft_handle_label_declaration(char *str, t_valid* valid)
{
	size_t		i;
	size_t		distance;
	char 		*temp;

	temp = NULL;
	distance = ft_strlen(str);
	if (ft_strchr(str, LABEL_CHAR) && !(i = 0))
	{
		distance = ft_strchr(str, LABEL_CHAR) - str;
		temp = ft_strsub(str, 0, distance + 1);
	}
	if (ft_strchr(temp, COMMENT_CHAR) || ft_strchr(temp, COMMENT_CHAR2) || ft_strchr(temp, LABEL_CHAR) == NULL)
	{
		valid->i += ft_check_label_chars(str, distance, valid);
	}
	else
	{
		while (str[i] && str[i] != LABEL_CHAR)
		{
			if (!ft_strchr(LABEL_CHARS, str[i]))
				((str[i] == SEPARATOR_CHAR || str[i] == ' ' || str[i] == '\t') && str[i + 1] != LABEL_CHAR) ? 0 : ft_lexical_err(valid);
			i++;
		}
		valid->i += i;
		valid->i += (str[i] == '\0') ? 0 : 1;
	}
	(temp == NULL) ? 0 : ft_memdel((void**)&temp);
}

void 		ft_handle_label_invocation(char *str, t_valid* valid)
{
	size_t		i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && i != 0)
		{
			if ((str = ft_handle_double_qoutes(valid)) == NULL)
				break ;
		}
		else if ((str[i] == COMMENT_CHAR2 || str[i] == COMMENT_CHAR) && i != 0)
			break ;
		else if (!ft_strchr(LABEL_CHARS, str[i]))
			((str[i] == SEPARATOR_CHAR || str[i] == ' ' || str[i] == '\t') && i != 0) ? 0 : ft_lexical_err(valid);
		i++;
	}
	valid->i += (str[i] == '\0') ? i : ft_strlen(str) - 1;
	(i == 0) ? ft_lexical_err(valid) : 0;
}

void		ft_handle_command(int command_id, t_valid *valid)
{
	valid->i += ft_strlen(op_tab[command_id].command_name);
}

size_t		ft_handle_register(char *str, t_valid *valid)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-' && !ft_isdigit(str[i + 1]))
		{
			printf("ERROR!\n");
			ft_lexical_err(valid);
		}
		else if ((str[i] == ' ' || str[i] == '\t') && str[i - 1] == '-')
		{
			printf("OR MAYBE ERROR IS HERE!!\n");
			ft_lexical_err(valid);
		}
		i++;
	}
	return (i);
}

size_t		ft_handle_indirect(char *str)
{
	return (ft_skip_chars(str, ft_isdigit, -1));
}

void		ft_check_str_chars(char *str, t_valid *valid)
{
	int 		command_id;
	char 		*temp;

	temp = str;
	str = ft_lstrip(str);
	valid->i += ft_strlen(temp) - ft_strlen(str);
	(str[valid->i] == '\0') ? ft_memdel((void**)&temp): 0;
	if (str[valid->i] == NAME_CMD_STRING[0] || str[valid->i] == COMMENT_CMD_STRING[0])
	{
		valid->i += ft_handle_dot(str + valid->i, valid);
	}
	else if (str[valid->i] == COMMENT_CHAR || str[valid->i] == COMMENT_CHAR2)
		valid->i = ft_strlen(str);
	else if (str[valid->i] == '"')
	{
		ft_handle_double_qoutes(valid);
		valid->i += 2;
	}
	else if ((command_id = ft_is_command(str + valid->i)) != -1)
	{
		ft_handle_command(command_id, valid);
	}
	else if (str[valid->i] == DIRECT_CHAR && str[valid->i + 1] == LABEL_CHAR)
	{
		valid->i += 2;
		ft_handle_label_invocation(str + valid->i, valid);
	}
	else if (str[valid->i] == 'r')
	{
		valid->i += 1;
		valid->i += ft_handle_register(str + valid->i, valid);
	}
	else if (str[valid->i] == LABEL_CHAR || ft_strchr(LABEL_CHARS, str[valid->i]))
	{
		if (str[valid->i] == LABEL_CHAR)
		{
			valid->i += 1;
			ft_handle_label_invocation(str + valid->i, valid);
		}
		else
		{
			ft_handle_label_declaration(str + valid->i, valid);
		}
	}
	else if (str[valid->i] == SEPARATOR_CHAR)
	{
		valid->i += ft_skip_chars(str, NULL, SEPARATOR_CHAR);
	}
	else if ((str[valid->i] == '-' && ft_isdigit(str[valid->i + 1])) || ft_isdigit(str[valid->i]) || (str[valid->i] == DIRECT_CHAR))
	{
		if (str[valid->i] == DIRECT_CHAR && ((str[valid->i + 1] == '-' && ft_isdigit(str[valid->i + 2])) || ft_isdigit(str[valid->i + 1])))
		{
			// i += (str[i + 1] == '-') ? 3 : 2;
			valid->i += (str[valid->i + 1] == '-') ? 2 : 1;
			valid->i += ft_handle_indirect(str + valid->i);//check if further are digits
		}
		else if (str[valid->i] == '-' && ft_isdigit(str[valid->i + 1]))
		{
			valid->i += 1;// i += 2;
			valid->i += ft_handle_indirect(str + valid->i);//check if further are digits
		}
		else if (ft_isdigit(str[valid->i]))
			valid->i += ft_handle_indirect(str + valid->i);//check if further are digits
		else
		{
			ft_lexical_err(valid);
		}
	}
	else
	{
		printf("ERROR!\n");
		(str[valid->i] != ' ' && str[valid->i] != '\t') ? ft_lexical_err(valid) : valid->i++;
	}
	printf("GOING FURTHER:%s\n", str + valid->i);
	(str[valid->i] != '\0' && (!valid->errors)) ? ft_check_str_chars(str, valid) : 0;
}

void		ft_lexical_validation(t_valid *valid)
{
	char 		*temp;

	temp = ft_strnew(0);
	while (valid->file[valid->line_num])
	{
		ft_memdel((void**)&temp);
		temp = ft_lstrip(valid->file[valid->line_num]);
		valid->i = ft_strlen(valid->file[valid->line_num]) - ft_strlen(temp);
		if (temp[0] != COMMENT_CHAR && temp[0] != COMMENT_CHAR2 && !ft_spaces_based_line(temp))
		{
			printf("GO HERE!\n");
			ft_check_str_chars(temp, valid);
		}
		valid->line_num++;
	}
	ft_memdel((void**)&temp);
}
