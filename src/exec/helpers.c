#include "../../includes/minishell.h"

void	error_msg(t_hell *hell, char **cmd, char *error, int exitcode)
{
	if (error)
		ft_putendl_fd(error, STDERR_FILENO);
	hell->lastexit = exitcode;
	hell->exec_error = 1;
	(void)cmd;
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
}

void	ft_wait(t_hell *hell, char **cmd)
{
	int		wstatus = 0;
	t_proc	*head_cpy;

	head_cpy = (*hell->head);
	while (head_cpy)
	{
		if (head_cpy->pid != 0 && waitpid(head_cpy->pid, &wstatus, 0) == -1)
		{
			error_msg(hell, cmd, "waitpid failed 1", WEXITSTATUS(wstatus));
			return ;
		}
		head_cpy = head_cpy->next;
	}
	hell->lastexit = WEXITSTATUS(wstatus);
	head_cpy = (*hell->head);
	while (head_cpy)
	{
		if (head_cpy->hdoc_present && head_cpy->hdoc_tmpfile)
			unlink(head_cpy->hdoc_tmpfile);
		head_cpy = head_cpy->next;
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