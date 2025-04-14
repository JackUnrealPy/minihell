#include "../../includes/minishell.h"

void	ft_echo(t_hell *hell, t_proc *head, char **cmd, int pipe)
{
	int	fd;
	int	i;

	fd = 1;
	i = 1;
	t_redir *redirs_cpy = (*head->redirs);
	if (!pipe)
	{
		while (redirs_cpy)
		{
			if (access(redirs_cpy->pathordel, F_OK) == -1)
			{
				ft_putstr_fd(redirs_cpy->pathordel, 2);
				error_msg(hell, cmd, ": no such file or directory", 1);
			}
			if (redirs_cpy->type == 1)
				fd = open(redirs_cpy->pathordel, \
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else if (redirs_cpy->type == 2)
				fd = open(redirs_cpy->pathordel, \
				O_CREAT | O_WRONLY | O_APPEND, 0644);
			redirs_cpy = redirs_cpy->next;
		}
	}
	if (head->cmd[1] && ft_strncmp(head->cmd[1], "-n", \
		ft_strlen(head->cmd[1])) == 0)
		i = 2;
	while (head->cmd[i])
	{
		ft_putstr_fd(head->cmd[i], fd);
		if (head->cmd[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (ft_strncmp(head->cmd[1], "-n", ft_strlen(head->cmd[1])) != 0)
		ft_putchar_fd('\n', fd);
	if (!pipe)
		close(fd);
}
