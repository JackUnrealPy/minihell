/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:14:59 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/06/11 17:02:07 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_sig_flag;

void	heredoc_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_sig_flag = SIGINT;
		rl_replace_line("", 0);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
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

void	hdoc_check_sig(t_hell *hell, char *cmd)
{
	if (!cmd)
	{
		ft_putstr_fd("Warning: here-document delimited by EOF\n", 2);
		hell->lastexit = 0;
		hell->hdoc_sig = 1;
	}
	else if (g_sig_flag == SIGINT)
	{
		hell->lastexit = 130;
		hell->hdoc_sig = 1;
		free(cmd);
	}
}

void	heredoc_loop(t_hell *hell, t_proc *head, t_redir *redirs)
{
	char	*cmd;

	signal(SIGINT, heredoc_sig);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		cmd = readline("> ");
		if (!cmd || g_sig_flag == SIGINT)
		{
			hdoc_check_sig(hell, cmd);
			break ;
		}
		if (break_heredoc(redirs, cmd))
		{
			free(cmd);
			break ;
		}
		expansion_heredoc(hell, head, &cmd);
		if (g_sig_flag != SIGINT)
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
