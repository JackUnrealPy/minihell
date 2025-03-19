#include "execution.h"

typedef struct s_heredoc
{
	int pipe_fd[2];
}	t_heredoc;

void	heredoc_loop(int argc, char **argv, t_heredoc *hdoc, int *fd)
{
	char	*buffer;
	int		append;

	append = 0;
	if (argc == 3)
	{
		if (append)
			*fd = open(argv[2], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			*fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (pipe(&hdoc->pipe_fd[0]) == -1)
	{
		printf("pipe error");
		exit(1);
	}
	while (1)
	{
		write(0, "> ", 2);
		buffer = get_next_line(0, 0);
		if (ft_strncmp(buffer, argv[1], ft_strlen(argv[1])) == 0)
		{
			free(buffer);
			get_next_line(0, 1);
			break ;
		}
		ft_putstr_fd(buffer, hdoc->pipe_fd[1]);
		free(buffer);
	}
}

void	heredoc(int argc, char **argv)
{
	t_heredoc hdoc;
	int		fd;
	int		cmd;
	int		redir;
	heredoc_loop(argc, argv, &hdoc, &fd);
	char	*args[2] = {"cat", NULL};

	cmd = 0;
	redir = 0;
	if (cmd)
	{
		dup2(hdoc.pipe_fd[0], STDIN_FILENO);
		if (redir)
		{
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		close(hdoc.pipe_fd[0]);
		close(hdoc.pipe_fd[1]);
		execve("/bin/cat", args, 0);
	}
	if (redir)
		close(fd);
	close(hdoc.pipe_fd[0]);
	close(hdoc.pipe_fd[1]);
}

int	main(int argc, char *argv[])
{
	if (argc == 1)
		return (0);
	heredoc(argc, argv);
	return (0);
}
