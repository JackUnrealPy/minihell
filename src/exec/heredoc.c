/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:14:59 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/05/13 19:01:36 by nrumpfhu         ###   ########.fr       */
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

void	generate_tmpfile(t_hell *hell, t_proc *head)
{
	char	rando_txt[10];
	char	rando_char;
	int		i;
	int		fd;

	(void)hell;
	i = 0;
	fd = open("/dev/urandom", O_RDONLY);
	while (i < 9)
	{
		read(fd, &rando_char, 1);
		if (ft_isalnum(rando_char))
			rando_txt[i++] = rando_char;
	}
	close(fd);
	rando_txt[9] = 0;
	head->hdoc_tmpfile = ft_malloc(hell, hell->freeme, ft_strjoin("/tmp/.",
				rando_txt));
}

void	expansion_heredoc(t_hell *hell, t_proc *head, char *buffer, char *tmp)
{
	int	i;

	if (buffer && (*head->redirs)->type == 4)
	{
		i = 0;
		while (buffer[i])
		{
			if (buffer[i] == '$')
			{
				tmp = buffer;
				buffer = ft_strchr(buffer, '$');
				ft_expand(hell, head, &buffer, 0);
				break ;
			}
			i++;
		}
	}
	(void)tmp;
}

int	break_heredoc(t_redir *redirs, char *buffer)
{
	if (!buffer)
	{
		ft_putstr_fd("Warning: here-document delimited by EOF\n", 2);
		return (1);
	}
	if (ft_strlen(buffer) == ft_strlen(redirs->pathordel) && ft_strncmp(buffer,
			redirs->pathordel, ft_strlen(redirs->pathordel)) == 0)
	{
		free(buffer);
		return (1);
	}
	return (0);
}

void	heredoc_loop(t_hell *hell, t_proc *head, t_redir *redirs)
{
	char	*buffer;
	char	*tmp;

	while (1)
	{
		buffer = readline("> ");
		tmp = NULL;
		expansion_heredoc(hell, head, buffer, tmp);
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
		if (tmp)
			free(tmp);
		else
			free(buffer);
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
