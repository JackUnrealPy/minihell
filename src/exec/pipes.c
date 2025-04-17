/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:37:05 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/04/17 03:58:25 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	initialise_pipes(t_hell *hell, t_proc *head, t_redir *redirs,
		char **cmd)
{
	t_proc	*current;
	t_redir	*tmp;
	int		i;

	(void)redirs;
	hell->hdoc_count[0] = 0;
	current = head;
	while (current)
	{
		tmp = (*current->redirs);
		while (tmp)
		{
			if (tmp && tmp->type == 3)
				hell->hdoc_count[0]++;
			tmp = tmp->next;
		}
		current = current->next;
	}
	hell->pipe_fd = ft_malloc(hell, hell->freeme, malloc(sizeof(int)
				* (hell->cmd_count - 1) * 2));
	hell->hdoc_fd = (int *)ft_malloc(hell, hell->freeme, malloc(sizeof(int)
				* hell->hdoc_count[0] * 2));
	i = 0;
	while (i < hell->cmd_count - 1)
	{
		if (pipe(&hell->pipe_fd[(i++) * 2]) == -1)
			error_msg(hell, cmd, "pipe() failed", errno);
	}
	if (hell->hdoc_count[0] > 0)
		hdoc_pipes(hell, (*hell->head));
}

void	create_cmd(t_hell *hell, t_proc *head, char **cmd)
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
		head->cmd_path = ft_malloc(hell, head->freeme, ft_strjoin("/bin/",
					head->cmd[0]));
	if (!head->cmd_path)
		error_msg(hell, cmd, "Memory allocation failed", 1);
	// if (access(head->cmd_path, R_OK | X_OK) == -1)
	// 	error_msg(hell, cmd, "Cannot read/execute command executable", 1);
}

void	ft_freeme(char **arr)
{
	int	i;

	i = 0;
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

	hdoc = heredoc_check((*head->redirs));
	create_cmd(hell, head, cmd);
	if (hdoc)
	{
		init_hdoc(hell, head, cmd);
		if (hell->exec_error)
			return;
	}
	head->pid = fork();
	if (head->pid == 0)
	{
		input_redirection(hell, head, cmd, i);
		output_redirection(hell, head, cmd, i);
		ft_close(hell);
		if (head->cmd)
		{
			if (determine_builtin(hell, head, cmd, 1))
			{
				ft_terminate(1, cmd);
				jump_ship(hell, 0);
			}
			execve(head->cmd_path, head->cmd, hell->envp);
			ft_putstr_fd(head->cmd[0], 2);
			error_msg(hell, cmd, ": command not found", 127);
		}
		(ft_terminate(1, cmd), jump_ship(hell, 1));
	}
}

void	ft_pipex(t_hell *hell, char **cmd)
{
	int		i;
	t_proc	*head_cpy;

	i = 0;
	head_cpy = (*hell->head);
	initialise_struct(hell, (*hell->head));
	initialise_pipes(hell, (*hell->head), (*(*hell->head)->redirs), cmd);
	while (i < hell->cmd_count)
	{
		children(head_cpy, hell, cmd, i);
		if (hell->exec_error)
			return ;
		i++;
		if (i < hell->cmd_count)
			head_cpy = head_cpy->next;
	}
	ft_close(hell);
	ft_wait(hell, cmd);
}
