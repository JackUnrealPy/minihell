#include "minishell.h"

int	ft_env(t_hell *hell, char **envp, int fd)
{

	// if (argv && argv[1])
	// 	return (perror("too many arguments"), 1);
	while (*envp)
	{
		ft_putendl_fd(*envp, fd);
		envp++;
	}
	return (0);
}