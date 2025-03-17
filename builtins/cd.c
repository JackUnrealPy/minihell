#include "builtins.h"

void ft_cd(char **argv)
{
    if (chdir("/bin") != 0)
        exit(errno);
}