#include "libft/libft.h"
#include "pipex.h"
#include <string.h>

void	error_handling(int argc)
{
	if (argc == 1)
		exit(0);
}

void	redirection(int argc, char **argv, char *txt, char *delimitor)
{
	int	redirection;
	int	fd;

	redirection = 0;
	if (argc >= 2)
	{
		if (redirection)
			fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (!redirection)
	{
		fd = 2;
		txt = ft_strjoin(txt, "\n");
	}
	ft_putstr_fd(txt, fd);
	close(fd);
	free(delimitor);
	free(txt);
}

void	heredoc(int argc, char **argv)
{
	char	buffer[1024];
	ssize_t	bytes_read;
	char	*delimitor;
	char	*txt;

	txt = ft_strdup("");
	delimitor = ft_strdup(argv[1]);
	if (!delimitor)
		(ft_putstr_fd("malloc failed", 2), 1);
	while (1)
	{
		write(0, "> ", 2);
		bytes_read = read(0, buffer, sizeof(buffer) - 1);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read - 1] = 0;
		if (strcmp(buffer, delimitor) == 0)
			break ;
		if (txt && ft_strlen(txt) > 0)
			txt = ft_strjoin(txt, "\n");
		txt = ft_strjoin(txt, buffer);
	}
	redirection(argc, argv, txt, delimitor);
}

int	main(int argc, char *argv[])
{
	error_handling(argc);
	heredoc(argc, argv);
	return (0);
}
