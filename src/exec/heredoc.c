/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:14:59 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/06/08 22:35:47 by nrumpfhu         ###   ########.fr       */
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

// void heredoc_sig(int sig)
// {
//     (void)sig;
//     g_sig_flag = SIGINT;
//     // Don't write newline here - let handle_sig do it
//     rl_replace_line("", 0);
//     rl_done = 1;  // This makes readline return immediately
// }

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
	char	*cmd;

	cmd = NULL;
	signal(SIGINT, heredoc_sig);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		cmd = readline("> ");
		if (!cmd || g_sig_flag == SIGINT)
		{
			if (g_sig_flag == SIGINT)
				hell->lastexit = 130;
			g_sig_flag = 0;
			free(cmd);
			break ;
		}
		expansion_heredoc(hell, head, &cmd);
		if (break_heredoc(redirs, cmd))
			break ;
		ft_putendl_fd(cmd, head->hdoc_fd);
		free(cmd);
	}
}

int	heredoc(t_hell *hell, t_proc *head, t_redir *redirs)
{
	if (heredoc_check(redirs) == 0)
		return (0);
	generate_tmpfile(hell, head);
	head->hdoc_fd = open(head->hdoc_tmpfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	heredoc_loop(hell, head, redirs);
	close(head->hdoc_fd);
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}
