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

char 		*ft_handle_double_qoutes(size_t *index, t_valid *valid)
{
	char 		*temp;
	size_t		i;
	int 		db_quote_flag;

	db_quote_flag = 1;
	// printf("VALID_>FILE:%zu\n", ft_strlen(valid->file[valid->line_num]) - (*index + 1));
	temp = ft_strsub(valid->file[valid->line_num], *index + 1, ft_strlen(valid->file[valid->line_num]));// - (*index + 1));
	printf("TEMP:%s\n", temp);
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
	*index = (temp[i] == '\0') ? 0 : i - 1;
	return ((temp[i] == '\0') ? NULL : temp);
}

void 		ft_name_cmmt(char *line, int flag, t_valid *valid)
{
	char		*str;
	size_t		i;

	str = ft_strsub(line, 0, ft_strlen((flag) ? NAME_CMD_STRING : COMMENT_CMD_STRING));
	if (ft_strcmp(((flag) ? NAME_CMD_STRING : COMMENT_CMD_STRING), str) == 0)
	{
		i = ft_strlen((flag) ? NAME_CMD_STRING : COMMENT_CMD_STRING);
		while (line[i])
		{
			if (line[i] == '"')
			{
				if ((line = ft_handle_double_qoutes(&i, valid)) == NULL)
					break ;
			}
			else if (line[i] == COMMENT_CHAR || line[i] == COMMENT_CHAR2)
				break ;
			else if (!ft_strchr(LABEL_CHARS, line[i]) && line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != SEPARATOR_CHAR)
				ft_lexical_err(valid->line_num, i, valid);
			i++;
		}
	}
	else
		ft_lexical_err(valid->line_num, 0, valid);
	ft_memdel((void**)&str);
}

void 		ft_handle_dot(char *str, t_valid* valid)
{
	if (ft_strstr(str, NAME_CMD_STRING))
	{
		ft_name_cmmt(str, 1, valid);
	}
	else if (ft_strstr(str, COMMENT_CMD_STRING))
	{
		ft_name_cmmt(str, 0, valid);
	}
	else
		ft_lexical_err(valid->line_num, 0, valid);
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
			// return (1);
		}
		ft_memdel((void**)&temp);
	}
	//(ft_isalpha(string[0])) ? /*Handle somehow*/ : 0;
	// ft_memdel((void**)&string);
	return (-1);
	// return (0);
}

size_t		ft_check_label_chars(char *str, size_t end, size_t *index, t_valid *valid)
{
	size_t		i;

	i = 0;
	while (i < end && str[i])
	{
		if (str[i] == COMMENT_CHAR2 || str[i] == COMMENT_CHAR)
			break ;
		else if (!ft_strchr(LABEL_CHARS, str[i]) && str[i] != SEPARATOR_CHAR && str[i] != ' ' && str[i] != '\t')
			ft_lexical_err(valid->line_num, i, valid);
		i++;
	}
	*index += (str[i] == '\0') ? i : ft_strlen(str) - 1;
	return (i);
}

void 		ft_handle_label_declaration(char *str, size_t *index, t_valid* valid)
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
		ft_check_label_chars(str, distance, index, valid);
	else
	{
		while (str[i] && str[i] != LABEL_CHAR)
		{
			if (!ft_strchr(LABEL_CHARS, str[i]))
			{
				((str[i] == SEPARATOR_CHAR || str[i] == ' ' || str[i] == '\t') && str[i + 1] != LABEL_CHAR) ? 0 : ft_lexical_err(valid->line_num, *index + i, valid);
				//(str[i + 1] == LABEL_CHAR || str[i + 1] == '\0') ? ft_lexical_err(valid->line_num, *index + i, valid) : 0; // some allowed chars -> ,' ''\t' // ft_lexical_err(valid->line_num, i, valid); 
			}
			i++;
		}
		*index += i;
		*index += (str[i] == '\0') ? 0 : 1;
	}
	(temp == NULL) ? 0 : ft_memdel((void**)&temp);
}

void 		ft_handle_label_invocation(char *str, size_t *index, t_valid* valid)
{
	size_t		i;
	
	i = 0;
	printf("STRING_CHAR:%s\n", str + i);
	while (str[i])
	{
		if (str[i] == '"' && i != 0)
		{
			// i += *index;
			printf("I AM HERE!!!!!!!!!!%zu | %c\n", i, str[i]);
			if ((str = ft_handle_double_qoutes(&i, valid)) == NULL)
			{
				// i -= *index;
				printf("YO!\n");
				break ;
			}
			// i -= *index;
			printf("Current char:%s\n", str + i);
		}
		else if ((str[i] == COMMENT_CHAR2 || str[i] == COMMENT_CHAR) && i != 0)
			break ;
		else if (!ft_strchr(LABEL_CHARS, str[i]))
			((str[i] == SEPARATOR_CHAR || str[i] == ' ' || str[i] == '\t') && i != 0) ? 0 : ft_lexical_err(valid->line_num, *index + i, valid);
		i++;
	}
	*index += (str[i] == '\0') ? i : ft_strlen(str) - 1;
	printf("BYE BYE!%zu\n", i);
	(i == 0) ? ft_lexical_err(valid->line_num, *index, valid) : 0;
}

void		ft_handle_indirect(char *str, size_t *index)
{

}

void		ft_handle_command(int command_id, char *str, size_t *index, t_valid *valid)
{
	char 		*temp;
	size_t		i;

	i = ft_strlen(op_tab[command_id].command_name);
	temp = ft_lstrip(str + i);
	*index += ft_strlen(str) - ft_strlen(temp);
	// while (temp[i])
	// {
	// 	else if (ft_isdigit(temp[i]))
	// 		ft_handle_indirect(temp, &i, valid);
	// 	else if (temp[i] == 'r' && ft_isdigit(temp[i + 1]))
	// 		ft_handle_register();
	// 	else if (temp[i] != ' ' && temp[i] != '\t')
	// 		ft_lexical_err(valid->line, i, valid);
	// 	i++;
	// }
}

// void		ft_handle_direct_numeric(char *str, size_t *index, t_valid *valid)
// {
// 	//%1 -> %-01
// 	size_t		i;

// 	i = 0;
// 	if (str[i] == '-')
// 		i++;
// 	if (str[i] == '0')
// 	while (str[i] && ft_isdigit(str[i]))
// }

void		ft_check_str_chars(char *str, size_t i, t_valid *valid)
{
	int 		command_id;
	char 		*temp;

	temp = str;
	str = ft_lstrip(str);
	valid->left_offset += ft_strlen(temp) - ft_strlen(str);
	ft_memdel((void**)&temp);
	if (str[i] == '"')
	{
		ft_handle_double_qoutes(&i, valid);
		i += 2;
	}
	else if ((command_id = ft_is_command(str)) != -1)
		ft_handle_command(command_id, str, &i, valid);
	else if (str[i] == DIRECT_CHAR && str[i + 1] == LABEL_CHAR)
	{
		i += 2;
		printf("HERE!%zu\n", i);
		ft_handle_label_invocation(str + i, &i, valid);
	}
	else if (str[i] == LABEL_CHAR || ft_strchr(LABEL_CHARS, str[i]))
	{
		if (str[i] == LABEL_CHAR)
		{
			i += 1;
			ft_handle_label_invocation(str + i, &i, valid);
		}
		else
			ft_handle_label_declaration(str + i, &i, valid);
	}
	else if (str[i] == SEPARATOR_CHAR)
	{
		while (str[i] && str[i] == SEPARATOR_CHAR)
			i++;
	}
	else
	{
		
		ft_lexical_err(valid->line_num, i, valid);
	}
	(str[i] != '\0' && (!valid->errors)) ? ft_check_str_chars(str, i, valid) : 0;
}

void		ft_lexical_validation(t_valid *valid)
{
	char 		*temp;

	temp = ft_strnew(0);
	while (valid->file[valid->line_num])
	{
		ft_memdel((void**)&temp);
		temp = ft_lstrip(valid->file[valid->line_num]);
		valid->left_offset = ft_strlen(valid->file[valid->line_num]) - ft_strlen(temp);
		if (temp[0] == NAME_CMD_STRING[0] || temp[0] == COMMENT_CMD_STRING[0])
			ft_handle_dot(temp, valid);
		else if (temp[0] != COMMENT_CHAR && temp[0] != COMMENT_CHAR2 && !ft_spaces_based_line(temp))
			ft_check_str_chars(temp, 0, valid);
		valid->line_num++;
	}
	ft_memdel((void**)&temp);
}
