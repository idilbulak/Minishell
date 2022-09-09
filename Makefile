NAME = minishell
GCC	= gcc
SRCS_DIR = src/
SRCS =	\
	tokenizer/tokenizer.c \
	tokenizer/tokenlist_utils.c \
	tokenizer/tokenizer_helper.c \
	tokenizer/tokenizer_helper2.c \
	tokenizer/tokenizer_checks.c \
	parser/parser.c \
	parser/parser_utils.c \
	parser/parser_helper.c \
	parser/parser_helper2.c \
	parser/parser_checks.c \
	parser/expander.c \
	parser/expander_helper.c \
	parser/expander_heredoc.c \
	parser/quote_remover.c \
	main.c \
	signals/signals.c \
	executor/exec.c \
	executor/exec_utils.c \
	executor/filed.c \
	executor/here_doc.c \
	executor/redirections.c \
	environment/env_symtab_utils.c \
	environment/env_symtab.c \
	environment/env_array.c \
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
FLAGS = -Wall -Wextra -Werror -fsanitize=address
HEADER = inc/minishell.h

all:	$(NAME)

$(NAME): $(OBJS) libft/libft.a
	@echo "\033[0;32mCompiling minishell..."
# @$(GCC) $(FLAGS) -L libft -l ft -L/Users/dsaat/.brew/opt/readline/lib -I/Users/dsaat/.brew/opt/readline/lib -lreadline -o $(NAME) $(OBJS)
# @$(GCC) $(FLAGS) -L libft -l ft -L/Users/ibulak/.brew/opt/readline/lib -I/Users/ibulak/.brew/opt/readline/lib -lreadline -o $(NAME) $(OBJS)
	@$(GCC) $(FLAGS) -L libft -l ft -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/lib -lreadline -o $(NAME) $(OBJS)
# $(GCC) $(FLAGS) -L libft -l ft -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include -lreadline -o $(NAME) $(OBJS)
	@echo "\033[0mDone!"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER)
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
	@mkdir -p $(OBJS_DIR){$(SUB_DIR)}
	@$(GCC) $(FLAGS) -c $< -o $@

libft/libft.a:
	@printf "\n"
	@$(MAKE) -C libft

clean:
	@echo "\033[0;31mCleaning libft..."
	@$(MAKE) -C libft clean
	@echo "Cleaning objects..."
	@rm -rdf $(OBJS_DIR)
	@printf "\033[0m"

fclean: clean
	@echo "\033[0;31mCleaning executable..."
	@rm -f $(NAME)
	@rm -f libft/libft.a
	@printf "\033[0m"

re: fclean all

.PHONY:	clean fclean re