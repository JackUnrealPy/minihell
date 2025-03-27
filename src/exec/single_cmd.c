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

void	ft_redirection(t_redir *redirs)
{
	int	input_fd;
	int	output_fd;

	if (!redirs)
		return ;
	input_fd = 0;
	output_fd = 1;
	while (redirs)
	{
		if (redirs->type == 0)
			input_fd = open(redirs->pathordel, O_RDONLY, 0644);
		else if (redirs->type == 1)
			output_fd = open(redirs->pathordel, O_CREAT | O_WRONLY | O_TRUNC,
					0644);
		else if (redirs->type == 2)
			output_fd = open(redirs->pathordel, O_CREAT | O_WRONLY | O_APPEND,
					0644);
		else
			continue ; // heredoc
		redirs = redirs->next;
	}
	if (input_fd > 2)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (output_fd > 2)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
}

void	single_cmd(t_proc *head, char **envp)
{
	if (ft_strncmp(head->cmd[0], "/bin/", 5) == 0 || ft_strncmp(head->cmd[0],
			"/usr/bin/", 9) == 0 || ft_strncmp(head->cmd[0], "../", 3) == 0)
		head->cmd_path = ft_strdup(head->cmd[0]);
	else
		head->cmd_path = ft_strjoin("/bin/", head->cmd[0]);
	if (!head->cmd_path)
		exit(1);
	// return(ft_freehell(head->cmd), 1);
	if (access(head->cmd_path, R_OK | X_OK) == -1)
		perror(head->cmd[0]);
	int status;
	head->pid = fork();
	ft_redirection(*(head->redirs));
	if (head->pid == 0)
	{
		execve(head->cmd_path, head->cmd, envp);
		exit(0);
	}
	waitpid(head->pid, &status, 0);
	free(head->cmd_path);
}