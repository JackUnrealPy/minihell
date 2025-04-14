#include "../../includes/minishell.h"

void	input_redirection(t_hell *hell, t_proc *head, char **cmd, int i)
{
	int		input_fd;
	t_redir	*tmp;

	tmp = (*head->redirs);
	while (tmp)
	{
		if (tmp && tmp->type == 0)
		{
			if (access(tmp->pathordel, F_OK) == -1)
			{
				ft_putstr_fd(tmp->pathordel, 2);
				error_msg(hell, cmd, ": no such file or directory", 1);
			}
			input_fd = open(tmp->pathordel, O_RDONLY, 0644);
			if (input_fd < 0)
			{
				ft_putstr_fd(tmp->pathordel, 2);
				error_msg(hell, cmd, ": permission denied", 1);
			}
			if (dup2(input_fd, STDIN_FILENO) == -1)
				error_msg(hell, cmd, "dup2 failed", 1);
			close(input_fd);
			return ;
		}
		else if (i != -1 && tmp->type == 3)
		{
			if (dup2(hell->hdoc_fd[(hell->hdoc_count[1]*2)-2], STDIN_FILENO) == -1)
				error_msg(hell, cmd, "dup2 failed", 1);
			return ;
		}
		tmp = tmp->next;
	}
	if (i > 0 && hell->pipe_fd)
	{
		if (dup2(hell->pipe_fd[(i - 1) * 2], STDIN_FILENO) == -1)
			error_msg(hell, cmd, "dup2 failed", 1);
	}
}

void	output_redirection(t_hell *hell, t_proc *head, char **cmd, int i)
{
	int output_fd;
	t_redir *tmp;

	tmp = (*head->redirs);
	while (tmp)
	{
		if (tmp->type == 1 || tmp->type == 2)
		{
			if (tmp->type == 1)
				output_fd = open(tmp->pathordel, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
				output_fd = open(tmp->pathordel, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (output_fd < 0)
			{
				ft_putstr_fd(tmp->pathordel, 2);
				error_msg(hell, cmd, ": permission denied", 1);
			}
			if (dup2(output_fd, STDOUT_FILENO) == -1)
				error_msg(hell, cmd, "dup2 failed", 1);
			close(output_fd);
			return ;
		}
		tmp = tmp->next;
	}
	if (i != -1 && i != hell->cmd_count - 1)
	{
		if (dup2(hell->pipe_fd[(i * 2) + 1], STDOUT_FILENO) == -1)
			error_msg(hell, cmd, "dup2 failed", 1);
	}
}
