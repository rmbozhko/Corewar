NAME = valid
CC = gcc

SRC = asm.c get_next_line.c lexical_validation.c syntax_validation.c asm_errors.c logical_validation.c ft_gathering.c

OBJ = $(SRC:.c=.o)
CFLAGS = -c 
#-Wall -Wextra -Werror
HEADER1 = asm.h
HEADER2 = op.h

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
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
