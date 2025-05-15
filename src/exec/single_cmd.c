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

void	single_cmd(t_hell *hell, t_proc *head, char **cmd)
{
	head->hdoc_present = heredoc(hell, head, (*head->redirs));
	if ((*head->redirs == NULL) && determine_builtin(hell, (*hell->head), cmd, 0))
	{
		return ;
	}
	int	status = 0;
	head->pid = fork();
	if (head->pid == 0)
	{
		input_redirection(hell, head, cmd, -1);
		output_redirection(hell, head, cmd, -1);
		//ft_close(hell);
		if (determine_builtin(hell, (*hell->head), cmd, 0))
		{
			if (hell->exec_error)
				exit(hell->lastexit);
			exit(0);
		}
		if (!head->cmd)
			exit (0);
		create_cmd(hell, head, cmd);
		if (hell->exec_error)
		{
			exit(127);
		}
		execve(head->cmd_path, head->cmd, hell->envp);
		ft_putstr_fd(head->cmd[0], 2);
		error_msg(hell, cmd, ": command not found", 127);
		exit(127);
	}
	if (head->cmd && head->cmd[0] && ft_strncmp(head->cmd[0], "exit", 4) == 0)
	{
		ft_exit(hell, head, cmd, -1);
		exit(hell->lastexit);
	}
	if (hell->exec_error)
		return;
	if (waitpid(head->pid, &status, 0) == -1)
		error_msg(hell, cmd, "waitpid failed", WEXITSTATUS(status));
	hell->lastexit = WEXITSTATUS(status);
	if (head->hdoc_present)
		unlink(head->hdoc_tmpfile);
}