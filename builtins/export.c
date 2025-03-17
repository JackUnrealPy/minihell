#include "builtins.h"

void	env_export(char **envp, int fd)
{
	int	a;
	int	b;
	int	start_quote;

	a = 0;
	while (envp[a])
	{
		b = 0;
		ft_putstr_fd("declare -x ", fd);
		start_quote = 1;
		while (envp[a][b])
		{
			ft_putchar_fd(envp[a][b], fd);
			if (envp[a][b] == '=' && start_quote)
			{
				ft_putchar_fd('"', fd);
				start_quote = 0;
			}
			if (envp[a][b + 1] == '\0')
				ft_putchar_fd('"', fd);
			b++;
		}
		ft_putstr_fd("\n", fd);
		a++;
	}
}

void	ft_export(char **envp)
{
	int		pipe_fd[2];
	int		status;
	pid_t	pid[2];
	char	*args[] = {"sort", NULL};

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid[0] = fork();
	if (pid[0] == 0)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			;
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		env_export(envp, STDOUT_FILENO);
		exit(0);
	}
	pid[1] = fork();
	if (pid[1] == 0)
	{
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			;
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		execve("/bin/sort", args, envp);
		exit(0);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid[0], &status, 0);
	waitpid(pid[1], &status, 0);
}
