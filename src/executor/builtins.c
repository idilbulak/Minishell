#include "../../libft/libft.h"
#include "../../inc/exec.h"
#include "../../inc/builtins.h"
#include <stdio.h>
#include <string.h>

int		ft_echo(char **argv)
{
	int i;

	i = 1;
	while (argv[i]) //'\n' not in list
	{    
        if (i == 1 && argv[i] && ft_strcmp(argv[i], "-n") == 0)
            i++;
        if (argv[i])
            printf("%s ", argv[i]);
        i++;
	}
    if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
        return (0);
	printf("\n");
	return (0);
}

void    init_builtins(t_builtins *builtins)
{
	builtins[0].name = "echo";
	builtins[0].funct = ft_echo;
	builtins[1].name = NULL;
}

int		is_builtin(char **args, t_child *child)
{
	t_builtins  builtins[7];
	int         j;

	j = 0;
	init_builtins(builtins);
	while (builtins[j].name)
	{
		if (ft_strcmp(args[0], builtins[j].name) == 0)
		{
			child->exit_code = builtins[j].funct(args);
			return (1);
		}
		j++;
	}
	return (0);
}	
