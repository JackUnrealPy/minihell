#include "builtins.h"

void ft_pwd(char **argv)
{
    char buf[PATH_MAX];

    getcwd(buf, sizeof(buf));
    printf("%s\n", buf);
}