/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:54:29 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/05/08 14:49:00 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	input_redirection(t_hell *hell, t_proc *head, char **cmd, int i)
{
	int		input_fd;
	t_redir	*tmp;

	tmp = (*head->redirs);
	while (tmp)
	{
		if (tmp->type == 3)
		{
			close(hell->hdoc_fd);
			hell->hdoc_fd = open("temp_hdoc", O_RDONLY);
			//ft_putstr_fd(head->cmd[0], hell->hdoc_fd);
			if (dup2(hell->hdoc_fd, STDIN_FILENO) == -1)
			{
				error_msg(hell, cmd, "dup2 failed 5", 1);
				return ;
			}
			close(hell->hdoc_fd);
			return ;
		}
		else if (tmp && tmp->type == 0)
		{
			if (access(tmp->pathordel, F_OK) == -1)
			{
				ft_putstr_fd(tmp->pathordel, 2);
				error_msg(hell, cmd, ": No such file or directory", 1);
			}
			input_fd = open(tmp->pathordel, O_RDONLY, 0644);
			if (input_fd < 0)
			{
				ft_putstr_fd(tmp->pathordel, 2);
				error_msg(hell, cmd, ": permission denied", 1);
				return ;
			}
			if (dup2(input_fd, STDIN_FILENO) == -1)
			{
				error_msg(hell, cmd, "dup2 failed 4", 1);
				return ;
			}
			close(input_fd);
			//return ;
		}

		tmp = tmp->next;
	}
	if (i > 0 && hell->pipe_fd)
	{
		if (dup2(hell->pipe_fd[(i - 1) * 2], STDIN_FILENO) == -1)
		{
			printf("i: %i\n", i);
			error_msg(hell, cmd, "dup2 failed 3", 1);
		}
	}
}

void	output_redirection(t_hell *hell, t_proc *head, char **cmd, int i)
{
	int		output_fd;
	t_redir	*tmp;

	tmp = (*head->redirs);
	while (tmp)
	{
		if (tmp->type == 1 || tmp->type == 2)
		{
			if (tmp->type == 1)
				output_fd = open(tmp->pathordel, O_CREAT | O_WRONLY | O_TRUNC,
						0644);
			else
				output_fd = open(tmp->pathordel, O_CREAT | O_WRONLY | O_APPEND,
						0644);
			if (output_fd < 0)
			{
				ft_putstr_fd(tmp->pathordel, 2);
				error_msg(hell, cmd, ": permission denied", 1);
				return ;
			}
			if (dup2(output_fd, STDOUT_FILENO) == -1)
			{
				error_msg(hell, cmd, "dup2 failed 2", 1);
				return ;
			}
			close(output_fd);
			return ;
		}
		tmp = tmp->next;
	}
	if (i != -1 && i != hell->cmd_count - 1)
	{
		if (dup2(hell->pipe_fd[(i * 2) + 1], STDOUT_FILENO) == -1)
			error_msg(hell, cmd, "dup2 failed 8", 1);
	}

}
