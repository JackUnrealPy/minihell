/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:37:05 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/05/08 15:00:20 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	initialise_pipes(t_hell *hell, t_proc *head, t_redir *redirs, char **cmd)
{
	int		i;

	(void)redirs;
	(void)head;
	hell->pipe_fd = ft_malloc(hell, hell->freeme, malloc(sizeof(int) * (hell->cmd_count - 1) * 2));
	i = 0;
	while (i < hell->cmd_count - 1)
	{
		if (pipe(&hell->pipe_fd[(i++) * 2]) == -1)
			error_msg(hell, cmd, "pipe() failed", errno);
	}
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
	create_cmd(hell, head, cmd);

	head->pid = fork();
	if (head->pid == 0)
	{
		input_redirection(hell, head, cmd, i);
		output_redirection(hell, head, cmd, i);
		ft_close(hell);
		if (!head->cmd || !head->cmd[0])
			exit(0);
		if (head->cmd && head->cmd[0] && determine_builtin(hell, head, cmd, 1))
		{
			ft_terminate(1, cmd);
			jump_ship(hell, 0);
		}
		if (execve(head->cmd_path, head->cmd, hell->envp) == -1)
		{
			ft_putstr_fd(head->cmd[0], 2);
			error_msg(hell, cmd, ": command not found", 127);
			exit(127);
		}
		//(ft_terminate(1, cmd), jump_ship(hell, 1));
	}
}

void	ft_pipex(t_hell *hell, char **cmd)
{
	int		i;
	t_proc	*head_cpy;

	i = 0;
	head_cpy = (*hell->head);
	initialise_struct(hell, (*hell->head));
	while (head_cpy)
	{
		heredoc(hell, (*head_cpy->redirs));
		if (hell->exec_error || hell->lastexit == 130)
			return ;
		head_cpy = head_cpy->next;
	}
	initialise_pipes(hell, (*hell->head), (*(*hell->head)->redirs), cmd);

	head_cpy = (*hell->head);
	while (i < hell->cmd_count)
	{
		children(head_cpy, hell, cmd, i);
		if (hell->exec_error)
			return ;
		i++;
		if (i < hell->cmd_count)
		{
			head_cpy = head_cpy->next;
		}
	}
	ft_close(hell);
	ft_wait(hell, cmd);
}
