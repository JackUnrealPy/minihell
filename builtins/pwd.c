#include "builtins.h"

int	ft_pwd(char **argv)
{
	(void)argv;
	char buf[PATH_MAX];
	char *success = NULL;
	success = getcwd(buf, sizeof(buf));
	if (success)
		return (printf("%s\n", buf), 1);
	return (1);
}