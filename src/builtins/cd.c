#include "../../includes/minishell.h"

void	ft_cd(char **argv)
{
	(void)argv;
	//char *path = ft_strjoin(argv[])
	if (chdir("/workspaces/minihell/src") != 0)
		exit(errno);
}

// change working directory
// change PWD in envp
// change path in terminal