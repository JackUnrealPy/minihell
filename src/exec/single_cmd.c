/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:37:05 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/06/04 19:38:00 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
int	is_builtin(t_proc *head);

void	single_cmd(t_hell *hell, t_proc *head)
{
	int	status;

	if (head->cmd && head->cmd[0])
		hell->cmd_count = 1;
	else
		hell->cmd_count = 0;
	head->hdoc_present = heredoc(hell, head, (*head->redirs));
	if ((head->cmd && head->cmd[0]) && ((ft_strcmp(head->cmd[0], "cd") == 0 \
	|| ft_strcmp(head->cmd[0], "exit") == 0  || (!(*head->redirs)))))
	{
		if (determine_builtin(hell, (*hell->head), 0))
			return ;
	}
	status = 0;
	children(head, hell, -1);
	if (head->cmd && head->cmd[0] && ft_strncmp(head->cmd[0], "exit", 4) == 0)
		ft_exit(hell, head, 0);
	if (hell->exec_error)
		return ;
	if (waitpid(head->pid, &status, 0) == -1)
		error_msg(hell, NULL, "waitpid failed", WEXITSTATUS(status));
	hell->lastexit = WEXITSTATUS(status);
	if (head->hdoc_present)
		unlink(head->hdoc_tmpfile);
}
