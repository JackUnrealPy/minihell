#include "../../includes/minishell.h"

void	error_msg(t_hell *hell, char **cmd, char *error, int exitcode)
{
	if (error)
		ft_putendl_fd(error, STDERR_FILENO);
	hell->lastexit = exitcode;
	if (cmd)
		ft_terminate(1, cmd);
	jump_ship(hell, exitcode);
}

void	ft_close(t_hell *hell)
{
	int	i;

	i = 0;
	while (i < (hell->cmd_count - 1) * 2)
	{
		close(hell->pipe_fd[i]);
		i++;
	}
	i = 0;
	while (i < (hell->hdoc_count * 2))
	{
		close(hell->hdoc_fd[i]);
		i++;
	}
}

void	ft_wait(t_hell *hell, char **cmd)
{
	int		wstatus;
	t_proc	*head_cpy;

	head_cpy = (*hell->head);
	while (head_cpy)
	{
		if (waitpid(head_cpy->pid, &wstatus, 0) == -1)
			error_msg(hell, cmd, "waitpid failed", WEXITSTATUS(wstatus));
		if ((*head_cpy->redirs) && (*head_cpy->redirs)->type == 3
			&& waitpid(head_cpy->hpid, &wstatus, 0) == 1)
			error_msg(hell, cmd, "waitpid failed", WEXITSTATUS(wstatus));
		if (head_cpy && head_cpy->next)
			head_cpy = head_cpy->next;
		else
			break ;
	}
}

void	initialise_struct(t_hell *hell, t_proc *head)
{
	t_proc *current;

	hell->cmd_count = 0;
	current = head;
	while (current)
	{
		current = current->next;
		hell->cmd_count++;
	}
}