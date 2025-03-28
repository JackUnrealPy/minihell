#include "../../includes/minishell.h"

void    error_msg(char *error, int errno)
{
    ft_putendl_fd(error, STDERR_FILENO);
    exit(errno);
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

void	ft_wait(t_hell *hell)
{
	int	wstatus;

	while ((*hell->head)->next)
	{
		if (waitpid((*hell->head)->pid, &wstatus, 0) == -1)
			exit(WEXITSTATUS(wstatus)); // and free
		if ((*(*hell->head)->redirs)->type == 3 && waitpid((*hell->head)->hpid,
				&wstatus, 0) == 1)
			exit(WEXITSTATUS(wstatus)); // and free
		(*hell->head) = (*hell->head)->next;
	}
	// free_struct(hell, WEXITSTATUS(wstatus));
}

void	initialise_struct( t_hell *hell, t_proc *head)
{
	t_proc	*current;

	hell->cmd_count = 0;
	current = head;
	while (current)
	{
		current = current->next;
		hell->cmd_count++;
	}
}