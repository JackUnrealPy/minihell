#include "../../includes/minishell.h"

extern int g_sig_flag;

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

void	heredoc(t_hell *hell, t_redir *redirs)
{
	char	*buffer = NULL;

	if (heredoc_check(redirs) == 0)
		return;
	g_sig_flag = 0;
	hell->hdoc_fd = open("temp_hdoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	// error handling for open
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
			break;
		}
		if (ft_strlen(buffer) == ft_strlen(redirs->pathordel) && ft_strncmp(buffer, redirs->pathordel, ft_strlen(redirs->pathordel)) == 0)
		{
			free(buffer);
			break ;
		}
		if (!g_sig_flag)
			ft_putendl_fd(buffer, hell->hdoc_fd);
		free(buffer);
	}
	close(hell->hdoc_fd);
}
