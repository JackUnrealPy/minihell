/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:37:05 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/05/13 19:31:48 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	initialise_pipes(t_hell *hell, t_proc *head, t_redir *redirs)
{
	int	i;

	(void)redirs;
	(void)head;
	hell->pipe_fd = ft_malloc(hell, hell->freeme, malloc(sizeof(int)
				* (hell->cmd_count - 1) * 2));
	i = 0;
	while (i < hell->cmd_count - 1)
	{
		if (pipe(&hell->pipe_fd[(i++) * 2]) == -1)
			error_msg(hell, NULL, "pipe() failed", errno);
	}
}

void	test_cmds(t_hell *hell, t_proc *head)
{
	char	*path_env;
	char	**path;
	char	*test_path;
	char	*path_cmd;
	int		i;

	i = 0;
	path_env = ft_malloc(hell, head->freeme, ft_getenv("PATH", hell->envp));
	if (!path_env[0])
	{
		error_msg(hell, head->cmd[0], ": No such file or directory", 127);
		return ;
	}
	path = ft_malloc(hell, head->freeme, ft_split(path_env, ":"));
	if (!path)
		return (error_msg(hell, NULL, "Memory allocation failed", 1));
	path_cmd = ft_malloc(hell, head->freeme, ft_strjoin("/", head->cmd[0]));
	while (path && path[i])
	{
		test_path = ft_malloc(hell, head->freeme, ft_strjoin(path[i],
					path_cmd));
		if (access(test_path, R_OK | X_OK) == 0)
		{
			head->cmd_path = ft_malloc(hell, head->freeme, test_path);
			break ;
		}
		free(test_path);
		i++;
	}
}


void	create_cmd(t_hell *hell, t_proc *head)
{
	head->cmd_path = NULL;
	if (!head->cmd)
		return ;
	else if (determine_builtin(hell, head, 1))
	{
		free_exit(hell, 0);
	}
	else if (ft_strchr(head->cmd[0], '/'))
	{
		head->cmd_path = ft_strdup(head->cmd[0]);
		if (access(head->cmd_path, F_OK) == -1)
			error_msg(hell, head->cmd[0], ": No such file or directory", 1);
		return ;
	}
	else
		test_cmds(hell, head);
	if (!head->cmd_path || access(head->cmd_path, X_OK) != 0)
	{
		error_msg(hell, head->cmd[0], ": command not found 1", 127);
		return ;
	}
}

void	ft_freeme(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
	arr = NULL;
}

void	children(t_proc *head, t_hell *hell, int i)
{
	head->pid = fork();
	if (head->pid == 0)
	{
		input_redirection(hell, head, i);
		output_redirection(hell, head, i);
		ft_close(hell);
		create_cmd(hell, head);
		if (hell->exec_error)
			free_exit(hell, 127);
		if (!head->cmd || !head->cmd[0])
			free_exit(hell, 0);
		if (execve(head->cmd_path, head->cmd, hell->envp) == -1)
		{
			error_msg(hell, head->cmd[0], ": command not found 2", 127);
			free_exit(hell, 127);
		}
	}
}

void	ft_pipex(t_hell *hell)
{
	int		i;
	t_proc	*head_cpy;

	i = 0;
	head_cpy = (*hell->head);
	initialise_struct(hell, (*hell->head));
	while (head_cpy)
	{
		head_cpy->hdoc_present = heredoc(hell, head_cpy, (*head_cpy->redirs));
		if (hell->exec_error || hell->lastexit == 130)
			return ;
		head_cpy = head_cpy->next;
	}
	initialise_pipes(hell, (*hell->head), (*(*hell->head)->redirs));
	head_cpy = (*hell->head);
	while (i < hell->cmd_count)
	{
		hell->exec_error = 0;
		children(head_cpy, hell, i);
		if (hell->exec_error)
			return ;
		i++;
		if (i < hell->cmd_count)
		{
			head_cpy = head_cpy->next;
		}
	}
	ft_close(hell);
	ft_wait(hell);
}
