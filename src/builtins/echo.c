#include "../../includes/minishell.h"

void	ft_echo(t_hell *hell, t_proc *head, char **cmd, int pipe)
{
	int	fd;
	int	i;

	fd = 1;
	i = 1;
	if (!pipe)
		fd = builtins_output(hell, head, cmd);
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
	if (pipe)
		close(fd);
}
