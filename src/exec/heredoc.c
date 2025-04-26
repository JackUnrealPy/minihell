#include "../../includes/minishell.h"

char	*ft_realloc(char *old, char *new)
{
	char	*combine;

	combine = ft_strjoin(old, new);
	free(old);
	free(new);
	return (combine);
}

// change to hidden file, no child
// what should ctrl c and ctrl d do in heredoc?
// ctrl d prints warning in bash
// ctrl c prints newline but stays in program
// shlvl never changes

void	heredoc_sig(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
		ft_putstr_fd("Warning: here-document delimited by end-of-file (wanted `change me')\n", 2);
		exit(1);
	}
}

void	single_heredoc(t_hell *hell, t_proc *head, t_redir *redirs, char **cmd)
{
	char	*buffer;
	char	*txt;

	hell->hdoc_count[0] = 1;
	txt = NULL;
	while (1)
	{
		signal(SIGINT, &heredoc_sig);
		signal(SIGQUIT, SIG_IGN);
		buffer = readline("> ");
		if (!buffer)
			break;
		if (ft_strlen(buffer) == ft_strlen(redirs->pathordel) && ft_strncmp(buffer, redirs->pathordel, ft_strlen(redirs->pathordel)) == 0)
		{
			free(buffer);
			break ;
		}
		buffer = ft_strjoin(buffer, "\n");
		txt = ft_realloc(txt, buffer);
	}
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
			free(txt);
		}
		return ;
	}
	free(txt);
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
	int wstatus = 0;
	head->hpid = fork();
	if (head->hpid == 0)
	{
		heredoc(hell, head, (*head->redirs), cmd);
		if (hell->exec_error)
			return ;
		ft_terminate(1, cmd);
		jump_ship(hell, 0);
	}
	if (waitpid(head->hpid, NULL, 0) == -1)
		error_msg(hell, cmd, "waitpid failedddd", WEXITSTATUS(wstatus));
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
	// int		flag;
	int		i;

	i = hell->hdoc_count[1];
	// flag = 0;
	if (dup2(hell->hdoc_fd[(i * 2) + 1], STDOUT_FILENO) == -1)
	{
		error_msg(hell, cmd, "dup2 failed", 1);
		return ;
	}
	while (1)
	{
		// write(STDIN_FILENO, "> ", 2);
		// buffer = get_next_line(0, &flag);
		// if (!buffer)
		// 	return ;
		// if (ft_strncmp(buffer, redirs->pathordel, ft_strlen(buffer) - 1) == 0)
		// {
		// 	free(buffer);
		// 	ft_close(hell);
		// 	break ;
		// }
		signal(SIGINT, &heredoc_sig);
		signal(SIGQUIT, SIG_IGN);
		buffer = readline("> ");
		if (!buffer)
			break;
		if (ft_strlen(buffer) == ft_strlen(redirs->pathordel) && ft_strncmp(buffer, redirs->pathordel, ft_strlen(redirs->pathordel)) == 0)
		{
			free(buffer);
			ft_close(hell);
			break ;
		}
	// 	buffer = ft_strjoin(buffer, "\n");
	// 	txt = ft_realloc(txt, buffer);
	// }
		ft_putstr_fd(buffer, hell->hdoc_fd[(i * 2) + 1]);
		free(buffer);
		(void)head;
	}
}
