/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:37:05 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/04/16 23:35:51 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	single_cmd(t_hell *hell, t_proc *head, char **cmd)
{
	int	status = 0;

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
		return ;
	}
	if (waitpid(head->pid, &status, 0) == -1)
		error_msg(hell, cmd, "waitpid failed", WEXITSTATUS(status));
	hell->lastexit = WEXITSTATUS(status);
}
