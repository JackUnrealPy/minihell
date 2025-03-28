#include "../../includes/minishell.h"

void	input_redirection(t_hell *hell, t_proc *head, int i)
{
	int		input_fd;
	t_redir	*tmp;

	tmp = (*head->redirs);
	while (tmp)
	{
		if (tmp && tmp->type == 0)
		{
			input_fd = open(tmp->pathordel, O_RDONLY, 0644);
			if (dup2(input_fd, STDIN_FILENO) == -1)
				return ; // free, error msg
			close(input_fd);
			return ;
		}
		else if (tmp->type == 3)
		{
			if (dup2(hell->hdoc_fd[i * 2], STDIN_FILENO) == -1)
				return ;
			return ;
		}
		tmp = tmp->next;
	}
	if (i > 0)
	{
		if (dup2(hell->pipe_fd[(i - 1) * 2], STDIN_FILENO) == -1)
			return ; // free_struct(data, errno);
	}
}

void	output_redirection(t_hell *hell, t_proc *head, int i)
{
	int		output_fd;
	t_redir	*tmp;

	tmp = (*head->redirs);
	while (tmp)
	{
		if (tmp->type == 1 || tmp->type == 2)
		{
			if (tmp->type == 1)
				output_fd = open(tmp->pathordel, O_CREAT | O_WRONLY | O_TRUNC,
						0644);
			else
				output_fd = open(tmp->pathordel, O_CREAT | O_WRONLY | O_APPEND,
						0644);
			dup2(output_fd, STDOUT_FILENO);
			close(output_fd);
			return ;
		}
		tmp = tmp->next;
	}
	if (i != hell->cmd_count - 1 && i != -1)
	{
		if (dup2(hell->pipe_fd[(i * 2) + 1], STDOUT_FILENO) == -1)
			return ; // free, error msg
	}
}