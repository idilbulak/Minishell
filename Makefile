SRCS	=	src/tokenizer/tokenizer.c src/tokenizer/tokenlist_utils.c src/tokenizer/tokenizer_helper.c \
	src/tokenizer/tokenizer_helper2.c \
	src/parser/parser.c src/parser/parser_utils.c src/parser/parser_checks.c \
	src/main.c src/libft.c src/signals.c

OBJS	= $(SRCS:.c=.o)

NAME	= minishell

GCC		= gcc

FLAGS	= -Wall -Wextra -Werror

HEADER = inc/minishell.h


all:	$(NAME)

$(NAME):	$(OBJS)
	$(GCC) $(FLAGS) -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include -lreadline -o $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(GCC) -c $< -I/usr/local/opt/readline/include   -o  $(<:.c=.o)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	clean fclean re