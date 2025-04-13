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
	//hell->pipe_fd = malloc(sizeof(int) * (hell->cmd_count - 1) * 2);
	// head->freeme = NULL;
	hell->pipe_fd = ft_malloc(hell, hell->freeme, malloc(sizeof(int) * (hell->cmd_count - 1) * 2));
	hell->hdoc_fd = (int *)ft_malloc(hell, hell->freeme, malloc(sizeof(int) * hell->hdoc_count * 2));
	// if (!hell->pipe_fd || !hell->hdoc_fd)
	// 	error_msg(hell, "Memory allocation failed", 1); // free, error msg
	i = 0;
	while (i < hell->cmd_count - 1)
	{
		if (pipe(&hell->pipe_fd[i++ * 2]) == -1)
			return ; // free, error msg
	}
	if (hell->hdoc_count > 0)
		hdoc_pipes(hell, (*hell->head));
}

void	create_cmd(t_hell *hell, t_proc *head)
{
	if (!head->cmd)
	{
		head->cmd_path = NULL;
		return ;
	}
	if (ft_strncmp(head->cmd[0], "/bin/", 5) == 0 || ft_strncmp(head->cmd[0],
			"/usr/bin/", 9) == 0 || ft_strncmp(head->cmd[0], "../", 3) == 0)
		head->cmd_path = ft_malloc(hell, head->freeme, ft_strdup(head->cmd[0]));
	else
		head->cmd_path = ft_malloc(hell, head->freeme, ft_strjoin("/bin/", head->cmd[0]));
	if (!head->cmd_path)
		error_msg(hell, "Memory allocation failed", 1);
	if (access(head->cmd_path, R_OK | X_OK) == -1)
		return ; // free cmd_path, error msg
}

void	ft_freeme(char **arr)
{
	int i = 0;
	while (arr[i])
		i++;
	while (i != 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
	arr = NULL;
}

void	children(t_proc *head, t_hell *hell, char **cmd, int i)
{
	int	hdoc;
	(void)cmd;
	hdoc = heredoc_check((*head->redirs));
	create_cmd(hell, head);
	if (hdoc)
		init_hdoc(hell, head, i);
	head->pid = fork();
	if (head->pid == 0)
	{
		input_redirection(hell, head, i);
		output_redirection(hell, head, i);
		ft_close(hell, 1);
		if (determine_builtin(hell, head, cmd, 1))
		{
			ft_terminate(1, cmd);
			jump_ship(hell, 0);
		}
		execve(head->cmd_path, head->cmd, hell->envp);
		(ft_terminate(1, cmd), close_proc(hell), exit(errno));
		// error msg
	}
}

void	ft_pipex(t_hell *hell, char **cmd)
{
	initialise_struct(hell, (*hell->head));
	initialise_pipes(hell, (*hell->head), (*(*hell->head)->redirs));
	int i = 0;
	t_proc *head_cpy = (*hell->head);
	while (i < hell->cmd_count)
	{
		children(head_cpy, hell, cmd, i);
		i++;
		if (i < hell->cmd_count)
			head_cpy = head_cpy->next;
	}
	ft_close(hell, 0);
	ft_wait(hell);
}