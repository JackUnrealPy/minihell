/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:37:05 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/05/20 23:33:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	initialise_pipes(t_hell *hell, t_proc *head, t_redir *redirs)
{
	int	i;

	(void)redirs;
	(void)head;
	hell->pipe_fd = ft_malloc(hell, hell->freeme, malloc(sizeof(int)
				* (hell->cmd_count - 1) * 2));
	i = 0;
	while (i < hell->cmd_count - 1)
	{
		if (pipe(&hell->pipe_fd[(i++) * 2]) == -1)
			error_msg(hell, NULL, "pipe() failed", errno);
	}
}

void	children(t_proc *head, t_hell *hell, int i)
{
	head->pid = fork();
	if (head->pid == 0)
	{
		redirection(hell, head, i);
		if (i >= 0)
			ft_close(hell);
		if (determine_builtin(hell, head, 1))
		{
			if (hell->exec_error)
				jump_ship(hell, hell->lastexit);
			jump_ship(hell, 0);
		}
		if (!head->cmd || !head->cmd[0])
			jump_ship(hell, 0);
		create_cmd(hell, head);
		if (hell->exec_error)
			jump_ship(hell, 127);
		execve(head->cmd_path, head->cmd, hell->envp);
		error_msg(hell, head->cmd[0], ": command not found", 127);
		jump_ship(hell, 127);
	}
}

void	child_loop(t_hell *hell, t_proc *head_cpy)
{
	int	i;

	i = 0;
	while (i < hell->cmd_count)
	{
		hell->exec_error = 0;
		children(head_cpy, hell, i);
		if (hell->exec_error)
			return ;
		i++;
		if (i < hell->cmd_count)
			head_cpy = head_cpy->next;
	}
}

void	ft_pipex(t_hell *hell)
{
	t_proc	*head_cpy;

	head_cpy = (*hell->head);
	initialise_struct(hell, (*hell->head));
	while (head_cpy)
	{
		head_cpy->hdoc_present = heredoc(hell, head_cpy, (*head_cpy->redirs));
		if (hell->exec_error || hell->lastexit == 130)
			return ;
		head_cpy = head_cpy->next;
	}
	initialise_pipes(hell, (*hell->head), (*(*hell->head)->redirs));
	head_cpy = (*hell->head);
	child_loop(hell, head_cpy);
	ft_close(hell);
	ft_wait(hell);
}
