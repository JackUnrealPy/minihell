#include "../../includes/minishell.h"

int		newline_check(char **cmd)
{
	int	i;

	i = 1;
	int n;
	if (cmd[1] && ft_strncmp(cmd[1], "-n", 2) == 0)
	{
		i = 1;
		n = 1;
		while (cmd[i] && ft_strncmp(cmd[i], "-n", 2) == 0)
		{
			n = 1;
			while (cmd[i][n] && cmd[i][n] == 'n')
				n++;
			if (cmd[i][n])
				return (-1);
			i++;
		}
	}
	else
		return (0);
	return (i);
}
void	ft_echo(t_hell *hell, t_proc *head, char **cmd, int pipe)
{
	int	fd;
	fd = 1;
	int i;
	int newline = newline_check(head->cmd);
	i = newline;
	if (newline < 0)
		i *= -1;
	else if (newline == 0)
		i = 1;
	while (head->cmd[i])
	{
		ft_putstr_fd(head->cmd[i], fd);
		if (head->cmd[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (newline <= 0)
		ft_putchar_fd('\n', fd);
	if (pipe)
		close(fd);
	(void)hell;
	(void)cmd;
}