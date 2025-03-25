#include "../../includes/minishell.h"

int	ft_env(t_redir *redirs, char **envp, int pipe)
{
	int fd = 1;
	if (!pipe)
	{
		while (redirs)
		{
			if (redirs->type == 1)
				fd = open(redirs->pathordel, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else if (redirs->type == 2)
				fd = open(redirs->pathordel, O_CREAT | O_WRONLY | O_APPEND, 0644);
			redirs = redirs->next;
		}
	}
	while (*envp)
	{
		ft_putendl_fd(*envp, fd);
		envp++;
	}
	if (fd != 1)
		close(fd);
	return (0);
}