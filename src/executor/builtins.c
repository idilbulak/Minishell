#include "libft.h"
#include "exec.h"
#include "builtins.h"
#include <stdio.h>
#include <string.h>

void	ft_exit(int errornumber, char *errormessage)
{
	// fprintf(stderr, "error: failed to execute command: %s\n", 
	// strerror(errno));
	perror(errormessage);
	exit(errornumber);
}

int		ft_echo(char **argv)
{
	int i;

	i = 1;
	while (argv[i])
	{    
		printf("%s ", argv[i]);
		i++;
	}
	printf("\n");
	return (0);//(errno);
}

void    init_builtins(t_builtins *builtins)
{
	builtins[0].name = "echo";
	builtins[0].funct = ft_echo;
	builtins[1].name = NULL;
}

int		is_builtin(t_ast *ast, t_child *child, int i)
{
	t_builtins  builtins[7];
	int         j;

	j = 0;
	init_builtins(builtins);
	while (builtins[j].name)
	{
		if (ft_strcmp(ast->args[i]->data[0], builtins[j].name) == 0)
		{
			child->return_status = builtins[j].funct(ast->args[i]->data);
			return (1);
		}
		j++;
	}
	return (0);
}	
