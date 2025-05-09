/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:37:05 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/05/09 17:13:25 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	single_cmd(t_hell *hell, t_proc *head, char **cmd)
{
	head->hdoc_present = heredoc(hell, head, (*head->redirs));
	if (determine_builtin(hell, (*hell->head), cmd, 0))
		return ;
	int	status = 0;
	if (!head->cmd)
	{
		hell->lastexit = 0;
		return ;
	}
	hell->cmd_count = 1;
	create_cmd(hell, head, cmd);
	head->pid = fork();
	if (head->pid == 0)
	{
		input_redirection(hell, head, cmd, -1);
		output_redirection(hell, head, cmd, -1);
		execve(head->cmd_path, head->cmd, hell->envp);
		ft_putstr_fd(head->cmd[0], 2);
		error_msg(hell, cmd, ": command not found", 127);
		exit(127);
	}
	if (hell->exec_error)
		return;
	if (waitpid(head->pid, &status, 0) == -1)
		error_msg(hell, cmd, "waitpid failed", WEXITSTATUS(status));
	hell->lastexit = WEXITSTATUS(status);
	if (head->hdoc_present)
		unlink(head->hdoc_tmpfile);
}
