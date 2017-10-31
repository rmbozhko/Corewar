/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:33:38 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/31 16:43:22 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

# define ARG_MAX_NUM 3
# define BUFF_SIZE 1
# define DUMP_FLAG "-a"
# define NL_CODE ft_strchr(temp, '\n')
# define S_C_SUB (NL_CODE - temp)
# define IF_FP ((fd < 0 || fd > 4096) || ((read(fd, buff, 0)) == -1 && !(head)))
# define IF_SP (!(line) || !(ft_memset(buff, 0, BUFF_SIZE + 1)))
# define MEMORY_COEF	1
# define GEN_INFO (valid->name && valid->cmmt)
# define VALIDATION_LAYERS_AMOUNT 3
# define POSS_CHRS(s, i) (s[i] == SEPARATOR_CHAR || s[i] == ' ' || s[i] == '\t')
# define CMMT(f, j, i) (f[j][i] == COMMENT_CHAR || f[j][i] == COMMENT_CHAR2)
# define DIRECT_CHARS(s, i) (s[i] == DIRECT_CHAR && s[i + 1] == LABEL_CHAR)
# define CURR_ELEM valid->file[valid->l_num][valid->i]
# define CURR_STRING valid->file[valid->l_num] + valid->i
# define NOT_SPACES (CURR_ELEM != ' ' && CURR_ELEM != '\t')
# define CALCULATE_REF_ADDR (ft_get_label_addr(arg->label) - oper->addr)
# define NAME_CHAR valid->file[valid->l_num][valid->i] == NAME_CMD_STRING[0]
# define CMMT_CHAR valid->file[valid->l_num][valid->i] == COMMENT_CMD_STRING[0]
# define GEN_INFO_STR (NAME_CHAR || CMMT_CHAR)

typedef struct				s_struct
{
	int						fd;
	char					*line;
	struct s_struct			*next;
}							t_struct;

typedef	struct				s_arg
{
	size_t					type;
	char					*value;
	char					*label;
}							t_arg;

typedef	struct				s_operations
{
	size_t					command;
	t_arg					**args;
	unsigned char			cod_byte;
	size_t					instr_len;
	size_t					addr;
	struct s_operations		*next;
}							t_operations;

typedef	struct				s_labels
{
	char					*name;
	size_t					f_key;
	struct s_labels			*next;
}							t_labels;

typedef	struct				s_assembler
{
	char					*name;
	char					*cmmt;
	t_labels				*label;
	t_operations			*oper;
	size_t					instr_counter;
	size_t					prog_size;
	char					*instructions;
}							t_assembler;
t_assembler					g_asm;

typedef	struct				s_valid
{
	char					**file;
	size_t					l_num;
	size_t					i;
	int						errors;
	int						name;
	int						cmmt;
	size_t					flag : 1;
}							t_valid;

void						ft_check_str_chars_add(char *str, t_valid *v);
char						*ft_validate_string(char *str);
size_t						ft_handle_err_desc_f_part(t_valid *v, char **err);
size_t						ft_is_gen_info_repeating(char *str, t_valid *v);
int							ft_find_label_char(char *temp);
void						ft_check_label_chars(char *s, size_t e, t_valid *v);
size_t						ft_label_reference(char *str, t_valid *valid);
size_t						ft_get_label_addr(char *str);
void						ft_handle_short_int(char **s, signed short int v);
void						ft_handle_instr_invoke(char *str, t_valid *v);
size_t						ft_validate_args(char **commands, int cmd_opcode);
size_t						ft_skip_chars(char *str, int (*f)(int), int c);
void						ft_handle_label_declaration(char *str, t_valid *v);
void						ft_handle_label_invocation(char *str, t_valid *v);
void						ft_handle_dot(char *str, t_valid *v);
char						*ft_syn_dot(char *str, t_valid *v, int db_count);
typedef void				(*t_ft_valid_layers)(t_valid* valid);
char						*ft_get_mltl_string(size_t i, size_t j, t_valid *v);
size_t						ft_handle_argument(char *s, int opcode, size_t arg);
void						ft_add_cmd_to_list(t_operations *oper);
void						ft_add_cmd_to_label_list(t_labels *label);
size_t						ft_count_prog_len(void);
void						ft_gen_info_errors_handling(t_valid *valid);
size_t						ft_syn_reg(t_valid *valid, char *str);
unsigned int				move_bits(unsigned int number);
void						ft_handle_args(t_arg *a, char **s, t_operations *o);
t_ft_valid_layers			*ft_init_layers(void);
void						ft_init(int fd, t_valid *valid);
void						ft_dump_info(void);
void						ft_write_file(char *f, t_operations *o, char *i);
void						ft_exception(char *str, int fd);
size_t						ft_get_label_size(size_t cmd_opcode);
void						ft_handle_error(void);
int							get_next_line(const int fd, char **line);
void						ft_lexical_validation(t_valid *valid);
void						ft_syntax_validation(t_valid *valid);
void						ft_lexical_err(t_valid *valid);
size_t						ft_till_is_word(char *str);
int							ft_is_command(char *str, t_valid *valid, size_t i);
size_t						ft_handle_indirect(char *str, t_valid *valid);
int							ft_space_based_line(char *str);
char						*ft_handle_double_qoutes(t_valid *v, int db_flag);
size_t						ft_is_label(t_valid *valid, size_t i);
void						ft_crt_error(char *s, char *t, t_valid *v, int f);
void						ft_syntax_error(t_valid *valid, char *err, int f);
size_t						ft_syn_handle_register(t_valid *valid, char *str);
void						ft_logical_validation(t_valid *valid);
void						ft_log_error(size_t i, size_t arg, int op, int f);
int							skip_whitespaces(char *str, int i);
size_t						ft_get_arg_type(char *str);
t_operations				*ft_create_command(size_t opcode, char **args);
t_operations				*ft_get_command(t_valid *v, size_t i, size_t j);
t_labels					*ft_create_label(char *str, size_t	key);
t_operations				*ft_log_handle_command(t_valid *valid, size_t j);
void						ft_check_label_appear(char **file, t_valid *valid);
size_t						ft_count_instr_len(t_operations *oper);
unsigned char				ft_get_cod_byte(t_operations *oper);
#endif
