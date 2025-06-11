/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:37:05 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/06/11 13:14:44 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	single_cmd(t_hell *hell, t_proc *head)
{
	if (head->cmd && head->cmd[0])
		hell->cmd_count = 1;
	else
		hell->cmd_count = 0;
	head->hdoc_present = heredoc(hell, head, (*head->redirs));
	if ((head->cmd && head->cmd[0] && head->cmd[0][0]) && \
	(ft_strcmp(head->cmd[0], "cd") == 0 || \
	ft_strcmp(head->cmd[0], "exit") == 0 || (!(*head->redirs))))
	{
		if (determine_builtin(hell, (*hell->head), 0))
			return ;
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (!hell->hdoc_sig)
		children(head, hell, -1);
	ft_wait(hell);
}
