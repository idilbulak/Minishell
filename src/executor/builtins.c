#include "../../libft/libft.h"
#include "../../inc/exec.h"
#include "../../inc/builtins.h"
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
			child->return_status = builtins[j].funct(args);
			return (1);
		}
		j++;
	}
	return (0);
}	
