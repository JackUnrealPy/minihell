/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:54:29 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/05/20 04:23:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirs_heredoc(t_hell *hell, t_proc *head)
{
	head->hdoc_fd = open(head->hdoc_tmpfile, O_RDONLY);
	if (head->hdoc_fd < 0)
		return (error_msg(hell, NULL, "could not open heredoc tmpfile", 1));
	if (dup2(head->hdoc_fd, STDIN_FILENO) == -1)
		return (error_msg(hell, NULL, "dup2 failed", 1));
	close(head->hdoc_fd);
}

void	redirs_error(t_hell *hell, char *pathordel, char *msg, int errnum)
{
	error_msg(hell, pathordel, msg, errnum);
	jump_ship(hell, errnum);
}

void	check_folder(t_hell *hell, char *path)
{
	char	*dir;
	int		len;
	char	*slash;

	dir = NULL;
	slash = ft_strrchr(path, '/');
	if (slash && slash != path)
	{
		len = slash - path;
		dir = ft_calloc(len + 1, sizeof(char));
		if (!dir)
			redirs_error(hell, path, ": memory error", 1);
		ft_strlcpy(dir, path, len + 1);
		if (access(dir, F_OK) == -1)
		{
			free(dir);
			redirs_error(hell, path, ": No such file or directory", 1);
		}
		free(dir);
	}
}

int	perform_redir(t_hell *hell, char *path, int redir_type)
{
	int	fd;

	if (path[0] == '$' && path[1])
		redirs_error(hell, path, ": ambiguous redirect", 1);
	check_folder(hell, path);
	if (redir_type == 1)
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir_type == 2)
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
	{
		if (access(path, F_OK) == -1)
			redirs_error(hell, path, ": No such file or directory", 1);
		fd = open(path, O_RDONLY, 0644);
	}
	if (fd < 0)
		return (error_msg(hell, path, ": permission denied", 1), 1);
	if (redir_type == 0 && dup2(fd, STDIN_FILENO) == -1)
		return (error_msg(hell, NULL, "dup2 failed", 1), 1);
	else if ((redir_type == 1 || redir_type == 2)
		&& dup2(fd, STDOUT_FILENO) == -1)
		return (error_msg(hell, NULL, "dup2 failed", 1), 1);
	close(fd);
	return (0);
}

void	redirection(t_hell *hell, t_proc *head, int i)
{
	t_redir	*tmp;

	tmp = (*head->redirs);
	while (tmp)
	{
		if (tmp->type == 3 || tmp->type == 4)
			return (redirs_heredoc(hell, head));
		else if (tmp && tmp->type >= 0 && tmp && tmp->type <= 2
			&& perform_redir(hell, tmp->pathordel, tmp->type))
			return ;
		tmp = tmp->next;
	}
	if (i > 0 && hell->pipe_fd && dup2(hell->pipe_fd[(i - 1) * 2],
			STDIN_FILENO) == -1)
		error_msg(hell, NULL, "dup2 failed", 1);
	if (i != -1 && i != hell->cmd_count - 1)
	{
		if (dup2(hell->pipe_fd[(i * 2) + 1], STDOUT_FILENO) == -1)
			error_msg(hell, NULL, "dup2 failed", 1);
	}
}
