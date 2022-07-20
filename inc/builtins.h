#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct  s_builtins
{
	char	*name;
	int		(*funct)(char **argv);
	int		builtin_count;
}				t_builtins;

void	init_builtins(t_builtins *builtins);
int     is_builtin(char **args, t_child *child);
int		ft_echo(char **argv);
int		ft_cd(char **argv);
int		ft_pwd(char **argv);
int		ft_export(char **argv);
int		ft_unset(char **argv);
int		ft_env(char **argv);
void	ft_exit(int errornumber, char *errormessage);

# endif
