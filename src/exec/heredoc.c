/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:14:59 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/06/08 15:53:13 by nrumpfhu         ###   ########.fr       */
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
	signal(SIGINT, heredoc_sig);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		hell->hdoc_cmd = readline("> ");
		if (!hell->hdoc_cmd)
		{
            g_sig_flag = 0;
            break;
        }
		if (break_heredoc(redirs, hell->hdoc_cmd))
		{
			break ;
		}
		expansion_heredoc(hell, head, &hell->hdoc_cmd);
		if (g_sig_flag == SIGINT)
		{
			g_sig_flag = 0;
			hell->lastexit = 130;
			break ;
		}
		if (!g_sig_flag)
			ft_putendl_fd(hell->hdoc_cmd, head->hdoc_fd);
		free(hell->hdoc_cmd);
	}
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
}

int	heredoc(t_hell *hell, t_proc *head, t_redir *redirs)
{
	if (heredoc_check(redirs) == 0)
		return (0);
	g_sig_flag = 0;
	generate_tmpfile(hell, head);
	head->hdoc_fd = open(head->hdoc_tmpfile, O_CREAT | O_RDWR | O_TRUNC, 0644);

	heredoc_loop(hell, head, redirs);
	
	close(head->hdoc_fd);
	return (1);
}
