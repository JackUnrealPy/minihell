#include "../../includes/minishell.h"
#include <linux/limits.h>


int	ft_pwd(t_redir *redirs, int pipe)
{
	char buf[PATH_MAX];
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
	char *success = NULL;
	success = getcwd(buf, sizeof(buf));
	if (!success)
		return (10); // free, error msg
	ft_putendl_fd(buf, fd);
	if (fd != 1)
		close(fd);
	return (1);
}