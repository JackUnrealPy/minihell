/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 04:18:25 by marvin            #+#    #+#             */
/*   Updated: 2025/06/11 19:32:37 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_close(t_hell *hell)
{
	int	i;

	i = 0;
	while (i < (hell->cmd_count - 1) * 2)
	{
		if (hell->pipe_fd[i] != -1)
			close(hell->pipe_fd[i]);
		else
			break ;
		i++;
	}
}

void	check_exitstatus(t_hell *hell, t_proc *head)
{
	int	wstatus;
	int	signal;
	int	sig;

	signal = 0;
	wstatus = 0;
	while (head)
	{
		if (head->pid > 0 && waitpid(head->pid, &wstatus, 0) == -1)
			return (error_msg(hell, NULL, "waitpid failed",
					WEXITSTATUS(wstatus)));
		if (WIFSIGNALED(wstatus))
		{
			sig = WTERMSIG(wstatus);
			if (sig == SIGINT || sig == SIGQUIT)
				signal = 1;
			hell->lastexit = 128 + sig;
		}
		else
			hell->lastexit = WEXITSTATUS(wstatus);
		head = head->next;
	}
	if (signal || (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGINT))
		write(1, "\n", 1);
}

void	ft_wait(t_hell *hell)
{
	t_proc	*head_cpy;

	head_cpy = (*hell->head);
	if (!hell->hdoc_sig)
		check_exitstatus(hell, head_cpy);
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
