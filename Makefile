NAME = minishell
GCC	= gcc
SRCS_DIR = src/
SRCS =	\
	tokenizer/tokenizer.c \
	tokenizer/tokenlist_utils.c \
	tokenizer/tokenizer_helper.c \
	tokenizer/tokenizer_checks.c \
	parser/parser.c \
	parser/parser_utils.c \
	parser/parser_helper.c \
	parser/parser_checks.c \
	main.c \
	signals/signals.c \
	executor/exec.c \
	executor/exec_utils.c \
	executor/filed.c \
	executor/redirections.c \
	executor/cmd_search.c \
	environment/symtab.c \
	environment/environment.c \
	builtins/builtins.c \
	builtins/ft_cd.c \
	builtins/ft_echo.c \
	builtins/ft_env.c \
	builtins/ft_exit.c \
	builtins/ft_export.c \
	builtins/ft_pwd.c \
	builtins/ft_unset.c
OBJS_DIR = obj/
SUB_DIR = tokenizer,parser,executor,environment,signals,environment,builtins
OBJS = $(SRCS:%.c=$(OBJS_DIR)%.o)
FLAGS = -Wall -Wextra -Werror
HEADER = inc/minishell.h

all:	$(NAME)

$(NAME): $(OBJS) libft/libft.a
	$(GCC) $(FLAGS) -L libft -l ft -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/lib -lreadline -o $(NAME) $(OBJS)
# $(GCC) $(FLAGS) -L libft -l ft -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include -lreadline -o $(NAME) $(OBJS)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER)
	@mkdir -p $(OBJS_DIR){$(SUB_DIR)}
	$(GCC) $(FLAGS) -c $< -o $@

libft/libft.a:
	$(MAKE) -C libft

clean:
	rm -rdf $(OBJS_DIR)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean all

.PHONY:	clean fclean re