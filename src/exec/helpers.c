/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 04:18:25 by marvin            #+#    #+#             */
/*   Updated: 2025/06/07 20:27:15 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_msg(t_hell *hell, char *var, char *error, int exitcode)
{
	if (error)
	{
		if (var)
			ft_putstr_fd(var, STDERR_FILENO);
		ft_putendl_fd(error, STDERR_FILENO);
	}
	hell->lastexit = exitcode;
	hell->exec_error = 1;
	if (hell->cmd_count > 1)
		ft_close(hell);
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

void	ft_wait(t_hell *hell)
{
	int		wstatus;
	t_proc	*head_cpy;
	int signal = 0;

	wstatus = 0;
	head_cpy = (*hell->head);
	while (head_cpy)
	{
		if (head_cpy->pid != 0 && waitpid(head_cpy->pid, &wstatus, 0) == -1)
		{
			error_msg(hell, NULL, "waitpid failed", WEXITSTATUS(wstatus));
			return ;
		}
		if (WIFSIGNALED(wstatus))
			signal = 1;
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
	if (signal)
	{
		write(1, "\n", 1);
	}
}

void	initialise_struct(t_hell *hell, t_proc *head)
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

void	ft_freeme(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
	arr = NULL;
}
