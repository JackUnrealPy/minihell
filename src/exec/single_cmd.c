/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:37:05 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/03/25 18:58:07 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	single_cmd(t_hell *hell, t_proc *head)
{
	create_cmd(head);
	int status;
	head->pid = fork();
	if (head->pid == 0)
	{
		input_redirection(hell, head, -1);
		output_redirection(hell, head, -1);
		execve(head->cmd_path, head->cmd, hell->envp);
		exit(0);
	}
	waitpid(head->pid, &status, 0);
	free(head->cmd_path);
}
