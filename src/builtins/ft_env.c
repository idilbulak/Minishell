#include "../../inc/environment.h"
#include <stdio.h>

int	ft_env(char **argv, t_symtab **symtab)
{
	char	**env;
	int		i;

	(void)argv;
	i = 0;
	env = create_env_array(symtab);
	if (!env)
		return (1);
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	delete_env_array(env);
	return (0);
}
