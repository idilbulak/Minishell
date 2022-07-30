#include "../../libft/libft.h"
#include "../../inc/exec.h"
#include "../../inc/builtins.h"

void    init_builtins(t_builtins *builtins)
{
	// builtins[0].name = "cd";
	// builtins[0].funct = ft_cd;
	builtins[0].name = "echo";
	builtins[0].funct = ft_echo;
	builtins[1].name = "env";
	builtins[1].funct = ft_env;
	// builtins[3].name = "exit";
	// builtins[3].funct = ft_exit;
	builtins[2].name = "export";
	builtins[2].funct = ft_export;
	builtins[3].name = "pwd";
	builtins[3].funct = ft_pwd;
	// builtins[6].name = "unset";
	// builtins[6].funct = ft_unset;
	builtins[4].name = NULL;
}

int		is_builtin(char **args, t_child *child, t_symtab **symtab)
{
	t_builtins  builtins[7];
	int         j;

	j = 0;
	init_builtins(builtins);
	while (builtins[j].name)
	{
		if (ft_strcmp(args[0], builtins[j].name) == 0)
		{
			child->exit_code = builtins[j].funct(args, symtab);
			return (0);
		}
		j++;
	}
	return (1);
}	
