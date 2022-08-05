#include "../../inc/environment.h"
#include <stdio.h>

int    ft_pwd(char **argv, t_symtab **symtab)
{
	char	*cwd;
	
	(void)symtab;
	(void)argv;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
