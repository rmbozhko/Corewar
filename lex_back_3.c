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
			i++;
		}
		if (!db_quote_flag)
			break ;
		ft_memdel((void**)&temp);
		valid->line_num++;
		temp = (valid->file[valid->line_num]) ? ft_strdup(valid->file[valid->line_num]) : temp;
	}
	valid->i += i;
	if (valid->file[valid->line_num] == NULL)
		return (NULL);
	return ((temp[i] == '\0') ? NULL : temp);
}

size_t 		ft_name_cmmt(char *line, int flag, t_valid *valid)
{
	char		*str;
	size_t		i;

	str = ft_strsub(line, 0, ft_strlen((flag) ? NAME_CMD_STRING : COMMENT_CMD_STRING));
	i = ft_strlen(str);
	if (ft_strcmp(((flag) ? NAME_CMD_STRING : COMMENT_CMD_STRING), str) == 0)
		i = ft_strlen((flag) ? NAME_CMD_STRING : COMMENT_CMD_STRING);
	else
		ft_lexical_err(valid);
	ft_memdel((void**)&str);
	return (i);
}

void 		ft_handle_dot(char *str, t_valid* valid)
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
	valid->i += i;
}

int			ft_is_command(char *str, t_valid *valid)
{
	int			i;
	char 		*temp;
	char 		*string;//

	string = str;
	str = ft_lstrip(str);
	i = -1;
	printf("STRING COMMAND TEST CASE:%s\n", str);
	while (op_tab[++i].count_args != 0)
	{
		if (ft_strlen(str) >= ft_strlen(op_tab[i].command_name)) // str instead string
			temp = ft_strsub(str, 0, ft_strlen(op_tab[i].command_name)); // str instead string
		else
			continue ;
		if (ft_strcmp(temp, op_tab[i].command_name) == 0)
		{
			printf("TRUELY COMMAND STR:%s\n", str);
			valid->i += ft_strlen(string) - ft_strlen(str);
			ft_memdel((void**)&str);
			return (i);
		}
		ft_memdel((void**)&temp);
	}
	printf("STR AS COMMAND:%s\n", str);
	return (-1);
}

void		ft_check_label_chars(char *str, size_t end, t_valid *valid)
{
	printf("%s | %zu | %zu\n",str, end, valid->i);
	while (valid->i < end && str[valid->i])
	{
		if (str[valid->i] == '"')
		{
			printf("%s | %zu | %zu\n",str + valid->i, end, valid->i);
			if ((str = ft_handle_double_qoutes(valid)) == NULL)
			{
				break ;
			}
		}
		else if (str[valid->i] == COMMENT_CHAR2 || str[valid->i] == COMMENT_CHAR)
			break ;
		else if (!ft_strchr(LABEL_CHARS, str[valid->i]) && str[valid->i] != SEPARATOR_CHAR && str[valid->i] != ' ' && str[valid->i] != '\t')
		{
			ft_lexical_err(valid);
		}
		valid->i++;
	}
	printf("STRING IS HERE: %s | %zu | %zu\n",str, end, valid->i);
	if (str != NULL)
		(!(str[valid->i] != '\0' && str[valid->i] != COMMENT_CHAR2 && str[valid->i] != COMMENT_CHAR)) ? valid->i = ft_strlen(str) - 1 : 0;
	// valid->i += (str[valid->i] != '\0' && str[valid->i] != COMMENT_CHAR2 && str[valid->i] != COMMENT_CHAR) ? 0 : ft_strlen(str) - 1;
	// return (i);
}

void 		ft_handle_label_declaration(char *str, t_valid* valid)
{
	size_t		distance;
	char 		*temp;

	temp = NULL;
	distance = ft_strlen(str);
	if (ft_strchr(str, LABEL_CHAR))
	{
		distance = ft_strchr(str, LABEL_CHAR) - str;
		temp = ft_strsub(str, 0, distance + 1);
	}
	if (ft_strchr(temp, COMMENT_CHAR) || ft_strchr(temp, '"') || ft_strchr(temp, COMMENT_CHAR2) || ft_strchr(temp, LABEL_CHAR) == NULL)
	{
		printf("YO________-------_____________DC DRE!%s|%zu|%c\n", str, distance, str[distance]);
		ft_check_label_chars(str, distance, valid);
		write(1, "OLA!\n", 5);
	}
	else
	{
		while (str[valid->i] && str[valid->i] != LABEL_CHAR)
		{
			if (!ft_strchr(LABEL_CHARS, str[valid->i]))
				((str[valid->i] == SEPARATOR_CHAR || str[valid->i] == ' ' || str[valid->i] == '\t') && str[valid->i + 1] != LABEL_CHAR) ? 0 : printf("MOVING FURTHER!\n"), ft_lexical_err(valid);
			valid->i++;
		}
		valid->i += (str[valid->i] == '\0') ? 0 : 1;
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

void		ft_handle_register(char *str, t_valid *valid)
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
	valid->i += i;
}

size_t		ft_handle_indirect(char *str, t_valid *valid)
{
	if (str[valid->i] == DIRECT_CHAR && ((str[valid->i + 1] == '-' && ft_isdigit(str[valid->i + 2])) || ft_isdigit(str[valid->i + 1])))
	{
		valid->i += (str[valid->i + 1] == '-') ? 2 : 1;
		valid->i += ft_skip_chars(str + valid->i, ft_isdigit, -1);
		return (1);
	}
	else if (str[valid->i] == '-' && ft_isdigit(str[valid->i + 1]))
	{
		valid->i += 1;
		valid->i += ft_skip_chars(str + valid->i, ft_isdigit, -1);
		return (1);
	}
	else if (ft_isdigit(str[valid->i]))
	{
		valid->i += ft_skip_chars(str + valid->i, ft_isdigit, -1);
		return (1);
	}
	else
	{
		printf("ERROR MIGHT BE HERE!\n");
		return (0);
	}
}

void		ft_check_str_chars(char *str, t_valid *valid)
{
	int 		command_id;
	char 		*temp;

	temp = str;
	// str = ft_lstrip(str + valid->i);
	// valid->i += ft_strlen(temp) - ft_strlen(str);
	(str[valid->i] == '\0') ? ft_memdel((void**)&temp): 0;
	printf("STRING AT THE BEGINNING:%s\n", str);
	if (str[valid->i] == NAME_CMD_STRING[0] || str[valid->i] == COMMENT_CMD_STRING[0])
	{
		printf("DOT CASE\n");
		ft_handle_dot(str + valid->i, valid);
	}
	else if (str[valid->i] == COMMENT_CHAR || str[valid->i] == COMMENT_CHAR2)
		valid->i = ft_strlen(str);
	else if (str[valid->i] == '"')
	{
		ft_handle_double_qoutes(valid);
		valid->i += 2;
	}
	else if ((command_id = ft_is_command(str + valid->i, valid)) != -1)
	{
		valid->i += ft_strlen(op_tab[command_id].command_name);
	}
	else if (str[valid->i] == DIRECT_CHAR && str[valid->i + 1] == LABEL_CHAR)
	{
		valid->i += 2;
		ft_handle_label_invocation(str + valid->i, valid);
	}
	else if (str[valid->i] == 'r')
	{
		
		ft_handle_register(str + (++valid->i), valid);
	}
	else if (str[valid->i] == LABEL_CHAR || ft_strchr(LABEL_CHARS, str[valid->i]))
	{
		(str[valid->i] == LABEL_CHAR) ? ft_handle_label_invocation(str + (++valid->i), valid)
										: printf("________>>>>>>>>>>>>>>>>>>>>>>>>>>>>------------\n"), ft_handle_label_declaration(str, valid);// : ft_handle_label_declaration(str + valid->i, valid);
	}
	else if (str[valid->i] == SEPARATOR_CHAR)
	{
		valid->i += ft_skip_chars(str, NULL, SEPARATOR_CHAR);
	}
	else if ((str[valid->i] == '-' && ft_isdigit(str[valid->i + 1])) || ft_isdigit(str[valid->i]) || (str[valid->i] == DIRECT_CHAR))
		(!ft_handle_indirect(str, valid)) ? ft_lexical_err(valid) : 0;
	else
	{
		(str[valid->i] != ' ' && str[valid->i] != '\t') ? printf("ERROR TYPE%s\n", str + valid->i), ft_lexical_err(valid) : valid->i++;
	}
	printf("GOING FURTHER:%s\n", str + valid->i);
	(str[valid->i] != '\0' && (!valid->errors) && valid->file[valid->line_num]) ? ft_check_str_chars(str, valid) : 0;
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
			ft_check_str_chars(valid->file[valid->line_num], valid);
		}
		valid->line_num++;
	}
	ft_memdel((void**)&temp);
}
