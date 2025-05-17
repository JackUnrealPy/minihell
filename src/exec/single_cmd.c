/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:37:05 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/05/13 18:22:40 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_child(t_hell *hell, int error)
{
	// close_proc(hell);
	throw_garbage(hell->freeme);
	// close_proc(hell);
	// throw_garbage((*hell->head)->freeme);
	if (hell->head)
		free(hell->head);
	exit(error);
}

void	single_cmd(t_hell *hell, t_proc *head)
{
	int	status;

	head->hdoc_present = heredoc(hell, head, (*head->redirs));
	if ((*head->redirs == NULL) && determine_builtin(hell, (*hell->head), 0))
	{
		return ;
	}
	status = 0;
	head->pid = fork();
	if (head->pid == 0)
	{
		input_redirection(hell, head, -1);
		output_redirection(hell, head, -1);
		if (determine_builtin(hell, (*hell->head), 0))
		{
			if (hell->exec_error)
				free_exit(hell, hell->lastexit);
			free_exit(hell, 0);
		}
		if (!head->cmd)
			free_exit(hell, 0);
		create_cmd(hell, head);
		// if (hell->exec_error)
		// 	exit(0); //free_exit(hell, 127);
		execve(head->cmd_path, head->cmd, hell->envp);
		error_msg(hell, head->cmd[0], ": command not found", 127);
		jump_ship(hell, 127); //exit_child(hell, 127); //free_exit(hell, 127);
	}
	if (head->cmd && head->cmd[0] && ft_strncmp(head->cmd[0], "exit", 4) == 0)
	{
		ft_exit(hell, head, -1);
		// exit(hell->lastexit);
	}
	if (hell->exec_error)
		return ;
	if (waitpid(head->pid, &status, 0) == -1)
		error_msg(hell, NULL, "waitpid failed", WEXITSTATUS(status));
	hell->lastexit = WEXITSTATUS(status);
	if (head->hdoc_present)
		unlink(head->hdoc_tmpfile);
}
