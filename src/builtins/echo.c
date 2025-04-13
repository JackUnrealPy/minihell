#include "../../includes/minishell.h"

void	ft_echo(t_proc *head, int pipe)
{
	int	fd;
	int	i;

	fd = 1;
	i = 1;
	if (!pipe)
	{
		while ((*head->redirs))
		{
			if ((*head->redirs)->type == 1)
				fd = open((*head->redirs)->pathordel, \
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else if ((*head->redirs)->type == 2)
				fd = open((*head->redirs)->pathordel, \
				O_CREAT | O_WRONLY | O_APPEND, 0644);
			(*head->redirs) = (*head->redirs)->next;
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
