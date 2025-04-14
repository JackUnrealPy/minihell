#include "../../includes/minishell.h"

void	error_msg(t_hell *hell, char *error, int i)
{
	(void)hell; // free hell
	ft_putendl_fd(error, STDERR_FILENO);
	if (i >= 0)
		exit(i);
}

void	ft_close(t_hell *hell, int child)
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
	(void)child;
}

void	ft_wait(t_hell *hell)
{
	int		wstatus;
	t_proc	*head_cpy;

	head_cpy = (*hell->head);
	while (head_cpy)
	{
		if (waitpid(head_cpy->pid, &wstatus, 0) == -1)
			exit(WEXITSTATUS(wstatus)); // and free
		if ((*head_cpy->redirs) && (*head_cpy->redirs)->type == 3
			&& waitpid(head_cpy->hpid, &wstatus, 0) == 1)
			exit(WEXITSTATUS(wstatus)); // and free
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