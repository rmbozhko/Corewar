#include "asm.h"
#include "op.h"

void		ft_lexical_err(int line_num, int char_index, t_valid *valid)
{
	ft_putstr("Lexical error at [");
	ft_putnbr(line_num + 1); // line number
	ft_putstr(":");
	ft_putnbr(valid->left_offset + char_index + 1); // index of char in line + num of spaces omitted by ft_lstrip function
	ft_putstr("]\n");
	valid->errors += 1;
	// exit(0);
}

char		**ft_realoc_n_copy(char **arr, size_t *len, size_t n, size_t memory_coef)
{
	char		**temp;
	size_t		i;

	i = 0;
	*len += memory_coef;
	temp = (char**)malloc((*len) * sizeof(char*));
	while (i < n)
	{
		temp[i] = ft_strdup(arr[i]);
		i++;
	}
	ft_free_bidarr(arr, ft_bidlen(arr));
	return (temp);
}

char 		**ft_read_file(const int fd)
{
	char 		**arr;
	size_t		i;
	size_t		len;
	char		*line;

	len = 10;
	arr = (char**)malloc(sizeof(char*) * len); // we have done something with it, and will also implement into lem_in
	i = 0;
	line = ft_strnew(0);
	while (get_next_line(fd, &line, ft_strnew(0)) > 0)
	{
		(i == len) ? arr = ft_realoc_n_copy(arr, &len, i, 5) : 0;
		arr[i++] = ft_strdup(line);
	}
	arr[i] = NULL;
	return (arr);
}

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

char		*ft_loop_over(char *str, char c, size_t *i, t_valid *valid)
{
	char 		*temp;

	temp = ft_strnew(0);
	while (valid->file[valid->line_num])
	{
		ft_memdel((void**)&temp);
		temp = ft_strip(valid->file[valid->line_num]);
		valid->left_offset = ft_strlen(valid->file[valid->line_num]) - ft_strlen(temp);
		while (temp[*i] != c && temp[*i])
			*i += 1;
		if (temp[(*i)++] == c)
			return (temp);
		*i = 0;
		valid->line_num++;
	}
}

int 		ft_name_cmmt(char *line, int flag, t_valid *valid)
{
	char 		*temp;
	char		*str;
	size_t		i;

	temp = ft_strip(line);
	printf("TEMP:%s\n", temp);
	str = ft_strsub(temp, 0, ft_strlen((flag) ? NAME_CMD_STRING : COMMENT_CMD_STRING));
	if (ft_strcmp(((flag) ? NAME_CMD_STRING : COMMENT_CMD_STRING), str) == 0)
	{
		i = ft_strlen((flag) ? NAME_CMD_STRING : COMMENT_CMD_STRING);
		while (temp[i])
		{
			if (temp[i] == '"')
			{
				i += 1;
				if ((temp = ft_loop_over(temp, '"', &i, valid)) == NULL)
					break ;
			}
			else if (temp[i] == COMMENT_CHAR || temp[i] == COMMENT_CHAR2)
				break ;
			else if (!ft_strchr(LABEL_CHARS, temp[i]) && temp[i] != ' ' && temp[i] != '\t' && temp[i] != '\n')
			{
				ft_lexical_err(valid->line_num, i, valid);
				break ;
			}
			i++;
		}
	}
	// ft_memdel((void**)&temp);
	//return ERROR
}

int 		ft_handle_dot(char *str, t_valid* valid)
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
		ft_lexical_err(valid->line_num, 0, valid); // Lexical error return -> .extend || .nam || .comme
}

int 		ft_handle_label(char *str, t_valid* valid)
{
	size_t		i;
	size_t		distance;
	char 		*temp;

	i = 0;
	//if (there is no LABEL_CHAR in string then we do not display lexical error as it is Syntax error -> Syntax error at token [TOKEN][008:009] ENDLINE)
	if (ft_strchr(str, LABEL_CHAR))
	{
		distance = ft_strchr(str, LABEL_CHAR) - str;
		temp = ft_strsub(str, 0, distance);
		distance = (ft_strchr(str, COMMENT_CHAR) || ft_strchr(str, COMMENT_CHAR2));
		// printf("distance:%d\n", distance);
		(distance == 1) ? printf("Exit lexical validation, as this case is Syntax Error\n"), exit(0) : 0;
		ft_memdel((void**)&temp);
		while (str[i] && str[i] != LABEL_CHAR)
		{
			if (!ft_strchr(LABEL_CHARS, str[i]))
			{
				// printf("OLOL:%d\n", valid->left_offset);
				ft_lexical_err(valid->line_num, i, valid);// Lexical error
			}
			i++;
		}
	 }
}

int 		ft_lexical_validation(t_valid* valid)
{
	char 		*temp;
	size_t		i;

	while (valid->file[valid->line_num])
	{
		temp = ft_lstrip(valid->file[valid->line_num]);
		valid->left_offset = ft_strlen(valid->file[valid->line_num]) - ft_strlen(temp); // used to show errors properly, but still be working with strings, which don't have spaces at the left side.
												// you simply add left_offset to char indicator when it is lexical error
		if (temp[0] == '.')
		{
			printf("Dot CASE\n");
			ft_handle_dot(temp, valid);
		}
		else if (!ft_strchr(LABEL_CHARS, temp[0]) && temp[0] != COMMENT_CHAR && temp[0] != COMMENT_CHAR2 && temp[0] != '"')
		{
			i = 0;
			while (temp[i])
			{
				if (!ft_strchr(LABEL_CHARS, temp[i]) && temp[i] != SEPARATOR_CHAR && temp[i] != ' ' && temp[i] != '\t' && temp[i] != '\n')
					ft_lexical_err(valid->line_num, i, valid);
				i++;
			}
		}
		else if (ft_strchr(LABEL_CHARS, temp[0]) && temp[0])
		{
			printf("Label case\n");
			ft_handle_label(temp, valid);
			//	handle custom label-function
		}
		valid->line_num++;
		// ft_memdel((void**)&temp);
	}
	return (1);
}