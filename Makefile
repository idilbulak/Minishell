YELLOW = \033[0;33m
PURPLE = \033[0;35m
GREEN = \033[0;32m
RESET = \033[0m

NAME = minishell
SRCS_DIR = src/
SRCS_LIST = \
	tokenizer/tokenizer.c tokenizer/tokenlist_utils.c tokenizer/tokenizer_helper.c \
	tokenizer/tokenizer_helper2.c \
	parser/parser.c parser/parser_utils.c parser/parser_checks.c \
	executor/exec.c \
	main.c libft.c signals.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))
OBJS = $(SRCS:.c=.o)
FLAGS = -lreadline
# LDFLAGS			=	-L/opt/homebrew/opt/readline/lib
# CPPFLAGS		=	-I/opt/homebrew/opt/readline/include
INC = -I ./inc

all: $(NAME)

$(NAME): $(OBJS) 
	@echo "$(PURPLE) compiling minishell $(RESET)"
	$(CC) $(FLAGS) $(INC) $(SRCS) -o $(NAME)

%.o: %.c
	$(CC) -c $(INC) $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: clean fclean all
# GREEN = \033[32m
# BLUE = \033[34m
# YELLOW = \e[0;33m
# RESET = \033[0m

# NAME			=	minishell

# NAME_BONUS		=	checker

# SRCS_DIR		=	./src/

# INCLUDES		=	./inc/

# AR				=	ar
# ARFLAGS			=	rcs

# SRCS_F			=	tokenizer/tokenizer.c tokenizer/tokenlist_utils.c tokenizer/tokenizer_helper.c \
# 					tokenizer/tokenizer_helper2.c \
# 					parser/parser.c parser/parser_utils.c parser/parser_checks.c \
# 					executor/exec.c \
# 					main.c libft.c signals.c
		

# SRCS			= 	$(addprefix $(SRCS_DIR), $(SRCS_F))

# OBJS 			= $(SRCS:.c=.o)

# CC				=	gcc
# CC_FLAGS		= 	-lreadline  #-Wall -Wextra -Werror
# LDFLAGS			=	-L/opt/homebrew/opt/readline/lib
# CPPFLAGS		=	-I/opt/homebrew/opt/readline/include

# all:			$(NAME)

# $(NAME):		$(OBJS)
# 				$(CC) $(CC_FLAGS) $(INCLUDES) $(SRCS) $(LDFLAGS) $(CPPFLAGS) -o $(NAME)
# 				@echo "$(GREEN)MINIHELL$(RESET)"

# %.o: %.c:			
# 				$(CC) -c $(INCLUDES)  $< -o $@

# clean:
# 	rm -f $(OBJS)
# fclean: clean
# 	rm -f $(NAME)
# re: fclean all
# .PHONY: all clean fclean re bonus