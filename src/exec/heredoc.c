/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:14:59 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/05/08 17:57:10 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_sig_flag;

char	*ft_realloc(char *old, char *new)
{
	char	*combine;

	combine = ft_strjoin(old, new);
	free(old);
	free(new);
	return (combine);
}

void	heredoc_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_sig_flag = SIGINT;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		// printf("\n");
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
	}
}

int	heredoc_check(t_redir *redirs)
{
	t_redir	*tmp;

	tmp = redirs;
	while (tmp)
	{
		if (tmp->type == 3)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	generate_tmpfile(t_hell *hell, t_proc *head)
{
	(void)hell;
	char rando_txt[10];
	char rando_char;
	int i = 0;
	int fd = open("/dev/urandom", O_RDONLY);
	while (i < 9)
	{
		read(fd, &rando_char, 1);
		if (ft_isalnum(rando_char))
			rando_txt[i++] = rando_char;
	}
	close(fd);
	rando_txt[9] = 0;
	head->hdoc_tmpfile = "TMP"; //ft_malloc(hell, hell->freeme, ft_strjoin("/tmp/.", rando_txt));
}

int	heredoc(t_hell *hell, t_proc *head, t_redir *redirs)
{
	(void)hell;
	char	*buffer;

	buffer = NULL;
	if (heredoc_check(redirs) == 0)
		return (0);
	g_sig_flag = 0;
	generate_tmpfile(hell, head);
	head->hdoc_fd = open(head->hdoc_tmpfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	signal(SIGINT, heredoc_sig);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		buffer = readline("> ");
		if (g_sig_flag == SIGINT)
		{
			g_sig_flag = 0;
			hell->lastexit = 130;
			break ;
		}
		if (!buffer)
		{
			ft_putstr_fd("Warning: here-document delimited by end-of-file (wanted `change me')\n", 2);
			break ;
		}
		if (ft_strlen(buffer) == ft_strlen(redirs->pathordel)
			&& ft_strncmp(buffer, redirs->pathordel,
				ft_strlen(redirs->pathordel)) == 0)
		{
			free(buffer);
			break ;
		}
		if (!g_sig_flag)
			ft_putendl_fd(buffer, head->hdoc_fd);
		free(buffer);
	}
	close(head->hdoc_fd);
	return (1);
}
