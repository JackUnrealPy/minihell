/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:14:59 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/05/20 04:19:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_sig_flag;

void	heredoc_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_sig_flag = SIGINT;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
}

int	heredoc_check(t_redir *redirs)
{
	t_redir	*tmp;

	tmp = redirs;
	while (tmp)
	{
		if (tmp->type == 3 || tmp->type == 4)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	heredoc_loop(t_hell *hell, t_proc *head, t_redir *redirs)
{
	char	*buffer;

	while (1)
	{
		buffer = readline("> ");
		expansion_heredoc(hell, head, &buffer);
		if (g_sig_flag == SIGINT)
		{
			g_sig_flag = 0;
			hell->lastexit = 130;
			break ;
		}
		if (break_heredoc(redirs, buffer))
			break ;
		if (!g_sig_flag)
			ft_putendl_fd(buffer, head->hdoc_fd);
	}
}

int	heredoc(t_hell *hell, t_proc *head, t_redir *redirs)
{
	if (heredoc_check(redirs) == 0)
		return (0);
	g_sig_flag = 0;
	generate_tmpfile(hell, head);
	head->hdoc_fd = open(head->hdoc_tmpfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	signal(SIGINT, heredoc_sig);
	signal(SIGQUIT, SIG_IGN);
	heredoc_loop(hell, head, redirs);
	close(head->hdoc_fd);
	return (1);
}
