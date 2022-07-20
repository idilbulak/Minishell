NAME = minishell
GCC	= gcc
SRC_DIR = src/
SRC	= \
	tokenizer/tokenizer.c \
	tokenizer/tokenlist_utils.c \
	tokenizer/tokenizer_helper.c \
	tokenizer/tokenizer_helper2.c \
	parser/parser.c \
	parser/parser_utils.c \
	parser/parser_checks.c \
	signals/signals.c \
	main.c 
OBJ_DIR = obj/
SUB_DIR = tokenizer,parser,executor,environment,signals
OBJ	= $(SRC:%.c=$(OBJ_DIR)%.o)
FLAGS = -Wall -Wextra -Werror
INC = -I inc #-I libft
#HEADER = inc/minishell.h

all: $(NAME)

$(NAME): $(OBJ) libft/libft.a
	$(GCC) $(FLAGS) -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/lib -lreadline -o $(NAME) $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.c #$(HEADER)
	@mkdir -p $(OBJ_DIR){$(SUB_DIR)}
	$(GCC) $(INC) -c $< -o $@

libft/libft.a:
	$(MAKE) -C libft

clean:
	rm -f $(OBJ)
	rm -rdf $(OBJ_DIR)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean all

.PHONY:	clean fclean re