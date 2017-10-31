NAME = asm
CC = gcc

SRC = asm.c get_next_line.c asm_lex_valid.c asm_syn_valid.c asm_errors.c asm_log_valid.c asm_gather.c asm_writing.c ft_bonus_output.c asm_init.c op.c asm_writing_additional.c asm_gather_additional.c asm_label_ref.c asm_lex_valid_additional.c asm_lex_valid_composite.c asm_lex_valid_helpers.c asm_log_valid_additional.c asm_log_valid_helpers.c asm_syn_valid_additional.c asm_syn_valid_composite.c asm_syn_valid_helpers.c

OBJ = $(SRC:.c=.o)
CFLAGS = -c -O3 -Wall -Wextra -Werror
HEADER1 = asm.h
HEADER2 = op.h

all: $(NAME)

$(NAME): $(OBJ)
	#@make -C libft 
	@$(CC) $(OBJ) -L./libft -lft -I$(HEADER1) -I$(HEADER2) -o $(NAME)
	@echo "\033[0;37mAsm validation is compiled\033[0m"

%.o : %.c $(HEADER1) $(HEADER2)
	@$(CC) $(CFLAGS) $<

clean:
	@make clean -C libft
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME)

re: fclean all
