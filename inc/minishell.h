#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include "tokenizer.h"
# include "parser.h"
# include "signals.h"
# include "signal.h"
# include "exec.h"
# include "filed.h"
# include "builtins.h"
# include "../libft/libft.h"

void	rl_replace_line (const char *text, int clear_undo);

#endif