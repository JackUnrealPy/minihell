/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:54:29 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/06/12 18:43:42 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirs_heredoc(t_hell *hell, t_proc *head)
{
	head->hdoc_fd = open(head->hdoc_tmpfile, O_RDONLY);
	if (head->hdoc_fd < 0)
		return (error_msg(hell, NULL, "could not open heredoc tmpfile", 1), 1);
	if (dup2(head->hdoc_fd, STDIN_FILENO) == -1)
		return (close(head->hdoc_fd), error_msg(hell, NULL, "dup2 failed", 1),
			1);
	close(head->hdoc_fd);
	return (1);
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

int	perform_redir(t_hell *hell, t_proc *head, char *path, int redir_type)
{
	int	fd;

	if (head->redirerr)
	{
		while ((*head->redirs)->next && (*head->redirs)->next->pathordel)
			(*head->redirs) = (*head->redirs)->next;
		redirs_error(hell, (*head->redirs)->pathordel, ": ambiguous redirect",
			1);
	}
	if (is_directory(path))
	{
		error_msg(hell, path, ": Is a directory", 1);
		jump_ship(hell, 1);
	}
	check_folder(hell, path);
	fd = open_fd(hell, path, redir_type);
	if (fd < 0)
		return (error_msg(hell, path, ": permission denied", 1), 1);
	if (redir_type == 0 && dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), error_msg(hell, NULL, "dup2 failed", 1), 1);
	else if ((redir_type == 1 || redir_type == 2) \
	&& dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), error_msg(hell, NULL, "dup2 failed", 1), 1);
	close(fd);
	return (1);
}

void	dup_fd(t_hell *hell, int redir_in, int redir_out, int i)
{
	if (i > 0 && hell->pipe_fd && !redir_in)
	{
		if (dup2(hell->pipe_fd[(i - 1) * 2], STDIN_FILENO) == -1)
			return (ft_close(hell), error_msg(hell, NULL, "dup2 failed", 1));
	}
	if (i != -1 && i < hell->cmd_count - 1 && !redir_out)
	{
		if (dup2(hell->pipe_fd[(i * 2) + 1], STDOUT_FILENO) == -1)
			return (ft_close(hell), error_msg(hell, NULL, "dup2 failed", 1));
	}
}

void	redirection(t_hell *hell, t_proc *head, int i)
{
	t_redir	*tmp;
	int		redir_in;
	int		redir_out;

	redir_out = 0;
	redir_in = 0;
	tmp = (*head->redirs);
	while (tmp)
	{
		if (tmp->type == 3 || tmp->type == 4)
		{
			if (!head->next)
				redir_in = 1;
			redirs_heredoc(hell, head);
		}
		else if (tmp && tmp->type >= 0 && tmp->type <= 2 && perform_redir(hell,
				head, tmp->pathordel, tmp->type))
		{
			if (tmp->type != 0 && head->next)
				redir_out = 1;
		}
		tmp = tmp->next;
	}
	dup_fd(hell, redir_in, redir_out, i);
}
