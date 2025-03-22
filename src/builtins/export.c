#include "../includesminishell.h"

void	env_export(char **my_envp, int fd)
{
	int	a;
	int	b;
	int	start_quote;

	a = 0;
	while (my_envp[a])
	{
		b = 0;
		ft_putstr_fd("declare -x ", fd);
		start_quote = 1;
		while (my_envp[a][b])
		{
			ft_putchar_fd(my_envp[a][b], fd);
			if (my_envp[a][b] == '=' && start_quote)
			{
				ft_putchar_fd('"', fd);
				start_quote = 0;
			}
			if (my_envp[a][b + 1] == '\0')
				ft_putchar_fd('"', fd);
			b++;
		}
		ft_putstr_fd("\n", fd);
		a++;
	}
}

void	close_pipes(int pipe1, int pipe2, int exitnum)
{
	close(pipe1);
	close(pipe2);
	if (exitnum > 0)
		exit(exitnum);
}
void	ft_export(char **my_envp)
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
			close_pipes(pipe_fd[0], pipe_fd[1], errno);
		close_pipes(pipe_fd[0], pipe_fd[1], 0);
		env_export(my_envp, STDOUT_FILENO);
		exit(0);
	}
	pid[1] = fork();
	if (pid[1] == 0)
	{
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			close_pipes(pipe_fd[0], pipe_fd[1], errno);
		close_pipes(pipe_fd[0], pipe_fd[1], 0);
		execve("/bin/sort", args, my_envp);
		exit(0);
	}
	close_pipes(pipe_fd[0], pipe_fd[1], 0);
	waitpid(pid[0], &status, 0);
	waitpid(pid[1], &status, 0);
}

char	**export_var(char **argv, char **my_envp, t_list *env_lst)
{
	//add_list_element(env_lst, argv[1]);
	my_envp = ft_realloc_envp(my_envp, 1, argv[1]);
	return(my_envp);
}

char	**export_init(int argc, char **argv, char **my_envp)
{
	//t_list *env_lst = create_env_list(envp);
	if (argc > 2)
		my_envp = export_var(argv + 1, my_envp, NULL);
	ft_export(my_envp);
	return(my_envp);
	
	//ft_lstclear(&env_lst, del);
}
