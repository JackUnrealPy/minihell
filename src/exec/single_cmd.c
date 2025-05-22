/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:37:05 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/05/22 16:16:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	single_cmd(t_hell *hell, t_proc *head)
{
	int	status;

	if (head->cmd && head->cmd[0])
		hell->cmd_count = 1;
	else
		hell->cmd_count = 0;
	head->hdoc_present = heredoc(hell, head, (*head->redirs));
	if (!(*head->redirs) && head->cmd && head->cmd[0]
		&& (ft_strcmp(head->cmd[0], "cd") == 0 || ft_strcmp(head->cmd[0],
				"exit") == 0 || ft_strcmp(head->cmd[0], "export") == 0)
		&& determine_builtin(hell, (*hell->head), 0))
		return ;
	status = 0;
	children(head, hell, -1);
	if (head->cmd && head->cmd[0] && ft_strncmp(head->cmd[0], "exit", 4) == 0)
		ft_exit(hell, head, -1);
	if (hell->exec_error)
		return ;
	if (waitpid(head->pid, &status, 0) == -1)
		error_msg(hell, NULL, "waitpid failed", WEXITSTATUS(status));
	hell->lastexit = WEXITSTATUS(status);
	if (head->hdoc_present)
		unlink(head->hdoc_tmpfile);
}
