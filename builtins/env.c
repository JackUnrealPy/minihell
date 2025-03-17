#include "builtins.h"

void	ft_env(char **envp, int fd)
{
	while (*envp)
	{
		ft_putstr_fd(*envp, fd);
		ft_putstr_fd("\n", fd);
		envp++;
	}
}