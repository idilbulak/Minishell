#include "../../inc/environment.h"
#include <unistd.h>

int	ft_cd(char **args, t_symtab **symtab)
{
	(void)symtab;
	if (chdir(args[1]) != 0)
	{
		perror(args[1]);
		return (1);
	}
	return (0);
}
