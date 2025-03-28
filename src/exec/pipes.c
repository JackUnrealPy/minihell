/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:37:05 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/03/25 18:56:13 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	initialise_pipes(t_hell *hell, t_proc *head, t_redir *redirs)
{
	t_proc	*current;
	t_redir	*tmp;
	int		i;

	(void)redirs;
	hell->hdoc_count = 0;
	current = head;
	while (current)
	{
		tmp = (*current->redirs);
		while (tmp)
		{
			if (tmp && tmp->type == 3)
				hell->hdoc_count++;
			tmp = tmp->next;
		}
		current = current->next;
	}
	hell->pipe_fd = malloc(sizeof(int) * (hell->cmd_count - 1) * 2);
	hell->hdoc_fd = malloc(sizeof(int) * hell->hdoc_count * 2);
	if (!hell->pipe_fd || !hell->hdoc_fd)
		return ; // free, error msg
	i = 0;
	while (i < hell->cmd_count - 1)
	{
		if (pipe(&hell->pipe_fd[i++ * 2]) == -1)
			return ; // free, error msg
	}
	if (hell->hdoc_count > 0)
		hdoc_pipes(hell, (*hell->head));
}

void	create_cmd(t_proc *head)
{
	if (!head->cmd)
	{
		head->cmd_path = NULL;
		return ;
	}
	if (ft_strncmp(head->cmd[0], "/bin/", 5) == 0 || ft_strncmp(head->cmd[0],
			"/usr/bin/", 9) == 0 || ft_strncmp(head->cmd[0], "../", 3) == 0)
		head->cmd_path = ft_strdup(head->cmd[0]);
	else
		head->cmd_path = ft_strjoin("/bin/", head->cmd[0]);
	if (!head->cmd_path)
		return ; // free, error msg
	if (access(head->cmd_path, R_OK | X_OK) == -1)
		return ; // free, error msg
}

void	children(t_proc *head, t_hell *hell, int i)
{
	int	hdoc;

	hdoc = heredoc_check((*head->redirs));
	create_cmd(head);
	if (hdoc)
		init_hdoc(hell, head, i);
	head->pid = fork();
	if (head->pid == 0)
	{
		input_redirection(hell, head, i);
		output_redirection(hell, head, i);
		// heredoc(hell, head, (*head->redirs));
		if (determine_builtin(hell, head, 1))
			exit(0);
		execve(head->cmd_path, head->cmd, hell->envp);
		ft_close(hell);
		exit(errno);
		// free, error msg
	}
}

void	ft_pipex(t_hell *hell)
{
	initialise_struct(hell, (*hell->head));
	initialise_pipes(hell, (*hell->head), (*(*hell->head)->redirs));
	int i = 0;
	while (i < hell->cmd_count)
	{
		children((*hell->head), hell, i);
		i++;
		if (i < hell->cmd_count)
			(*hell->head) = (*hell->head)->next;
	}
	ft_close(hell);
	ft_wait(hell);

	// free
}