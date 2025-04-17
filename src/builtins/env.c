#include "../../includes/minishell.h"

int	ft_env(t_redir *redirs, char **envp, int pipe)
{
	int fd = 1;
	t_redir *redirs_cpy = redirs;
	if (!pipe)
	{
		while (redirs_cpy)
		{
			if (redirs_cpy->type == 1)
				fd = open(redirs_cpy->pathordel, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else if (redirs_cpy->type == 2)
				fd = open(redirs_cpy->pathordel, O_CREAT | O_WRONLY | O_APPEND, 0644);
			redirs_cpy = redirs_cpy->next;
		}
	}
	int i = 0;
	while (envp[i])
	{
		ft_putendl_fd(envp[i], fd);
		i++;
	}
	if (fd != 1)
		close(fd);
	return (0);
}