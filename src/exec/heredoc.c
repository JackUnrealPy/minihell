#include "../../includes/minishell.h"

char	*ft_realloc(char *old, char *new)
{
	char	*combine;

	combine = ft_strjoin(old, new);
	free(old);
	free(new);
	return (combine);
}

// change so that pipes and single command both use same heredoc functions
// maybe change to hidden file

void	single_heredoc(t_hell *hell, t_proc *head, t_redir *redirs, char **cmd)
{
	char	*buffer;
	char	*txt;
	int		flag;

	hell->hdoc_count[0] = 1;
	txt = NULL;
	flag = 0;
	while (1)
	{
		write(STDIN_FILENO, "> ", 2);
		buffer = get_next_line(0, &flag);
		if (!buffer)
			return ;
		if (ft_strncmp(buffer, redirs->pathordel, ft_strlen(redirs->pathordel)) == 0)
		{
			free(buffer);
			break ;
		}
		txt = ft_realloc(txt, buffer);
	}


	// if (redirs->type == 4)
	// int i = 0;
	// while (txt[i] && txt[i] != '$')
	// 	i++;
	// ft_expand(hell, head, &txt, i);



	output_redirection(hell, head, cmd, -1);
	create_cmd(hell, head, cmd);
	if (hell->exec_error)
	{
		free(txt);
		return ;
	}
	if (head->cmd_path && ft_strncmp(head->cmd_path, "/bin/cat", 8) == 0)
	{
		if (txt)
		{
			ft_putstr_fd(txt, 1);
			// free(txt);
		}
		return ;
	}
	// free(txt);
	if (head->cmd_path)
	{
		if (!determine_builtin(hell, (*hell->head), cmd, 0))
			single_cmd(hell, (*hell->head), cmd);
	}
}

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

void	init_hdoc(t_hell *hell, t_proc *head, char **cmd)
{
	head->hpid = fork();
	if (head->hpid == 0)
	{
		heredoc(hell, head, (*head->redirs), cmd);
		if (hell->exec_error)
			return ;
		ft_terminate(1, cmd);
		jump_ship(hell, 0);
	}
	waitpid(head->hpid, NULL, 0);
	hell->hdoc_count[1]++;
}

int	hdoc_pipes(t_hell *hell, t_proc *head)
{
	int	i;

	(void)head;
	i = 0;
	while (i < hell->hdoc_count[0] * 2)
	{
		pipe(&hell->hdoc_fd[i]);
		i += 2;
	}
	return (0);
}

void	heredoc(t_hell *hell, t_proc *head, t_redir *redirs, char **cmd)
{
	char	*buffer;
	int		flag;
	int		i;

	i = hell->hdoc_count[1];
	flag = 0;
	if (dup2(hell->hdoc_fd[(i * 2) + 1], STDOUT_FILENO) == -1)
	{
		error_msg(hell, cmd, "dup2 failed", 1);
		return ;
	}
	while (1)
	{
		write(STDIN_FILENO, "> ", 2);
		buffer = get_next_line(0, &flag);
		if (!buffer)
			return ;
		if (ft_strncmp(buffer, redirs->pathordel, ft_strlen(buffer) - 1) == 0)
		{
			free(buffer);
			ft_close(hell);
			break ;
		}
		ft_putstr_fd(buffer, hell->hdoc_fd[(i * 2) + 1]);
		free(buffer);
		(void)head;
	}
}
