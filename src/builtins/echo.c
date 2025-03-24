#include "../../includes/minishell.h"

// char	**ft_double_strdup(char **args)
// {
// 	int		a;
// 	int		b;
// 	char	**cpy;

// 	a = 0;
// 	while (args[a])
// 		a++;
// 	b = a;
// 	cpy = ft_calloc(a + 1, sizeof(char *));
// 	a = 0;
// 	while (a < b)
// 	{
// 		cpy[a] = ft_strdup(args[a]);
// 		a++;
// 	}
// 	cpy[a] = NULL;
// 	return (cpy);
// }

void	ft_echo(t_proc *head, int pipe)
{
	int fd = 1;
	if (!pipe)
	{
		while (head->redirs)
		{
			if (head->redirs->type == 1)
				fd = open(head->redirs->pathordel, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else if (head->redirs->type == 2)
				fd = open(head->redirs->pathordel, O_CREAT | O_WRONLY | O_APPEND, 0644);
			head->redirs = head->redirs->next;
		}
	}
	int i = 1;
	if (head->cmd[1] && head->cmd[1] == "-n")
		i = 2;
	while (head->cmd[i])
	{
		ft_putstr_fd(head->cmd[i], fd);
		if (head->cmd[i+1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (head->cmd[1] != "-n")
		ft_putchar_fd('\n', fd);
	if (!pipe)
		close(fd);
}
