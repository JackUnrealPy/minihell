/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:54:29 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/05/17 17:07:24 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	input_redirection(t_hell *hell, t_proc *head, int i)
{
	int		input_fd;
	t_redir	*tmp;
	int		len;

	tmp = (*head->redirs);
	while (tmp)
	{
		if (tmp->type == 3 || tmp->type == 4)
		{
			head->hdoc_fd = open(head->hdoc_tmpfile, O_RDONLY); // check return
			if (dup2(head->hdoc_fd, STDIN_FILENO) == -1)
				return (error_msg(hell, NULL, "dup2 failed", 1));
			close(head->hdoc_fd);
			return ;
		}
		else if (tmp && tmp->type == 0)
		{
			if (tmp->pathordel[0] == '$' && tmp->pathordel[1])
			{
				error_msg(hell, tmp->pathordel, ": ambiguous redirect", 1);
				exit(1);
			}
			if (ft_strrchr(tmp->pathordel, '/'))
			{
				len = ft_strrchr(tmp->pathordel, '/') - tmp->pathordel;
				char dir[len + 1];
				strncpy(dir, tmp->pathordel, len); // update libft
				dir[len] = 0;
				if (access(dir, F_OK) == -1)
				{
					error_msg(hell, tmp->pathordel,
						": No such file or directory", 1);
					free_exit(hell, 1);
				}
			}
			if (access(tmp->pathordel, F_OK) == -1)
			{
				error_msg(hell, tmp->pathordel, ": No such file or directory",
					1);
				free_exit(hell, 1);
			}
			input_fd = open(tmp->pathordel, O_RDONLY, 0644);
			if (input_fd < 0)
			{
				error_msg(hell, tmp->pathordel, ": permission denied", 1);
				return ;
			}
			if (dup2(input_fd, STDIN_FILENO) == -1)
				return (error_msg(hell, NULL, "dup2 failed", 1));
			close(input_fd);
		}
		tmp = tmp->next;
	}
	if (i > 0 && hell->pipe_fd && dup2(hell->pipe_fd[(i - 1) * 2],
			STDIN_FILENO) == -1)
		error_msg(hell, NULL, "dup2 failed", 1);
}

void	output_redirection(t_hell *hell, t_proc *head, int i)
{
	int		output_fd;
	t_redir	*tmp;
	int		len;

	tmp = (*head->redirs);
	while (tmp)
	{
		if (tmp->type == 1 || tmp->type == 2)
		{
			if (tmp->pathordel[0] == '$' && tmp->pathordel[1])
			{
				error_msg(hell, tmp->pathordel, ": ambiguous redirect", 1);
				exit(1);
			}
			if (ft_strrchr(tmp->pathordel, '/'))
			{
				len = ft_strrchr(tmp->pathordel, '/') - tmp->pathordel;
				char dir[len + 1];
				strncpy(dir, tmp->pathordel, len); // update libft
				dir[len] = 0;
				if (access(dir, F_OK) == -1)
				{
					error_msg(hell, tmp->pathordel,
						": No such file or directory", 1);
					free_exit(hell, 1);
				}
			}
			if (tmp->type == 1)
				output_fd = open(tmp->pathordel, O_CREAT | O_WRONLY | O_TRUNC,
						0644);
			else
				output_fd = open(tmp->pathordel, O_CREAT | O_WRONLY | O_APPEND,
						0644);
			if (output_fd < 0)
				return (error_msg(hell, tmp->pathordel, ": permission denied",
						1));
			if (dup2(output_fd, STDOUT_FILENO) == -1)
				return (error_msg(hell, NULL, "dup2 failed", 1));
			close(output_fd);
		}
		tmp = tmp->next;
	}
	if (i != -1 && i != hell->cmd_count - 1)
	{
		if (dup2(hell->pipe_fd[(i * 2) + 1], STDOUT_FILENO) == -1)
			error_msg(hell, NULL, "dup2 failed", 1);
	}
}