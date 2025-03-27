#include "../../includes/minishell.h"

int	heredoc_check(t_redir *redirs)
{
	t_redir	*tmp;

	tmp = redirs;
	while (tmp)
	{
		if (tmp->type == 3)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	init_hdoc(t_hell *hell, t_proc *head, int i)
{
	head->hpid = fork();
	if (head->hpid == 0)
	{
		heredoc(hell, head, (*head->redirs), i);
		exit(0);
	}
	waitpid(head->hpid, NULL, 0);
}

int	hdoc_pipes(t_hell *hell, t_proc *head)
{
	int	i;

	(void)head;
	i = 0;
	while (i < hell->hdoc_count * 2)
	{
		pipe(&hell->hdoc_fd[i]);
		i += 2;
	}
	return (0);
}
void	heredoc(t_hell *hell, t_proc *head, t_redir *redirs, int i)
{
	char	*buffer;
	int		flag;

	flag = 0;
	(void)head;
	if (dup2(hell->hdoc_fd[(i * 2) + 1], STDOUT_FILENO) == -1)
		return ; // free, error msg
	while (1)
	{
		write(STDIN_FILENO, "> ", 2);
		buffer = get_next_line(0, &flag);
		if (!buffer)
			return ;
		if (ft_strncmp(buffer, redirs->pathordel, ft_strlen(buffer)) == 0)
		{
			free(buffer);
			ft_close(hell);
			break ;
		}
		// if (head->cmd && head->cmd[0])
		ft_putstr_fd(buffer, hell->hdoc_fd[(i * 2) + 1]);
		free(buffer);
	}
}
