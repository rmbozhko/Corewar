#ifndef ASM_H
# define ASM_H

# include <stdio.h>
# include "libft/libft.h"
# include <fcntl.h>

# define BUFF_SIZE 1
# define NL_CODE ft_strchr(temp, '\n')
# define S_C_SUB (NL_CODE - temp)
# define IF_FP ((fd < 0 || fd > 4096) || ((read(fd, buff, 0)) == -1 && !(head)))
# define IF_SP (!(line) || !(ft_memset(buff, 0, BUFF_SIZE + 1)))
# define MEMORY_COEF	1

void			ft_handle_error(void);
int				get_next_line(const int fd, char **line, char *str);

typedef		struct 	s_arg
{
	size_t			type;
	char			*arg;
}				   	t_arg;

typedef		struct s_operations
{
	char 					*command;
	char 					*method;
	t_arg					args[3];
	struct s_operations		*next;
}				   t_operations;

typedef		struct 	s_valid
{
	char		**file;
	int			line_num;
	int			left_offset;
	int			errors;
	int			name;
	int			cmmt;
}					t_valid;


char 				**ft_read_file(const int fd);
void 				ft_lexical_validation(t_valid* valid);
void 				ft_syntax_validation(t_valid* valid);
void				ft_lexical_err(int line_num, int char_index, t_valid *valid);
void				ft_check_str_chars(char *str, size_t i, t_valid *valid);
#endif
