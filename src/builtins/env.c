#include "minishell.h"

int	ft_env(char **argv, char **envp, int fd)
{
	(void)argv;
	// if (argv && argv[1])
	// 	return (perror("too many arguments"), 1);
	while (*envp)
	{
		ft_putendl_fd(*envp, fd);
		envp++;
	}
	return (0);
}