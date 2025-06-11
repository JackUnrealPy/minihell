/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:37:05 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/06/11 16:33:33 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_sig_flag;

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
		{
			hell->pipe_fd[(i - 1) * 2] = -1;
			error_msg(hell, NULL, "pipe() failed", errno);
			jump_ship(hell, 1);
		}
	}
}

int	is_directory(char *cmd)
{
	struct stat	buf;

	if (cmd[0] == '~' && (!cmd[1] || cmd[1] == '/'))
		return (1);
	if (stat(cmd, &buf) == 0 && S_ISDIR(buf.st_mode))
		return (1);
	return (0);
}

void	check_cmd_exists(t_hell *hell, t_proc *head)
{
	if (!head->cmd)
		jump_ship(hell, 0);
	if (!head->cmd || !head->cmd[0] || !head->cmd[0][0])
	{
		error_msg(hell, NULL, ": command not found", 127);
		jump_ship(hell, 127);
	}
	if (head->cmd[0][0] != '.' && is_directory(head->cmd[0]))
	{
		error_msg(hell, head->cmd[0], ": Is a directory", 126);
		jump_ship(hell, 126);
	}
}

void	children(t_proc *head, t_hell *hell, int i)
{
	head->pid = fork();
	if (head->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		redirection(hell, head, i);
		if (i >= 0)
			ft_close(hell);
		check_cmd_exists(hell, head);
		if (head->cmd && head->cmd[0] && determine_builtin(hell, head, 1))
		{
			if (hell->exec_error)
				jump_ship(hell, hell->lastexit);
			jump_ship(hell, 0);
		}
		create_cmd(hell, head);
		if (hell->exec_error)
			jump_ship(hell, hell->lastexit);
		execve(head->cmd_path, head->cmd, hell->envp);
		error_msg(hell, head->cmd[0], ": command not found", 127);
		jump_ship(hell, 127);
	}
}

void	child_loop(t_hell *hell, t_proc *head_cpy)
{
	int	i;

	i = 0;
	while (i < hell->cmd_count)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		hell->exec_error = 0;
		children(head_cpy, hell, i);
		if (hell->exec_error || head->redirerr)
			return ;
		i++;
		if (i < hell->cmd_count)
			head_cpy = head_cpy->next;
	}
}

void	ft_pipex(t_hell *hell)
{
	t_proc	*head_cpy;

	head_cpy = (*hell->head);
	initialise_struct(hell, (*hell->head));
	while (head_cpy)
	{
		head_cpy->hdoc_present = heredoc(hell, head_cpy, (*head_cpy->redirs));
		if (hell->exec_error || g_sig_flag == SIGINT)
			return ;
		head_cpy = head_cpy->next;
	}
	initialise_pipes(hell, (*hell->head), (*(*hell->head)->redirs));
	head_cpy = (*hell->head);
	if (!hell->hdoc_sig)
		child_loop(hell, head_cpy);
	ft_close(hell);
	ft_wait(hell);
}
