#include "../../inc/environment.h"
#include <stdio.h>

int    ft_pwd(char **argv, t_symtab **symtab)
{
    t_symtab    *tmp;
    
    (void)argv;
    tmp = symtab_lookup(symtab, "PWD");
    if (!tmp)
        return (1);
    printf("%s\n", tmp->value);
    return (0);
}
