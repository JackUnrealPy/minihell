#include "execution.h"

void	free_heredoc(char *delimitor, char *txt, char *path)
{
	free(delimitor);
	free(txt);
	free(path);
}

int	redirection(int argc, char **argv)
{
	int		redirection;
	int		fd;
	char	*path;

	redirection = 0;
	if (argc >= 2)
	{
		if (redirection)
			path = ft_strdup(argv[2]);
		else
			path = ft_strdup(".heredoc");
		// if (append)
		// 	fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		// else
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	return (fd);
}

void	heredoc(int argc, char **argv)
{
	char	*buffer;
	int		fd;
	char	*path;

	if (argc == 3)
		path = ft_strdup(argv[2]);
	else
		path = ft_strdup(".heredoc");
	// if (append)
	// 	fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	// else
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
		ft_putstr_fd(buffer, fd);
		free(buffer);
	}
	close(fd);
	if (argc == 2)
		unlink(path);
	free(path);
}

// int	main(int argc, char *argv[])
// {
// 	if (argc == 1)
// 		return (0);
// 	heredoc(argc, argv);
// 	return (0);
// }
