#include "../../includes/minishell.h"

int	determine_builtin(int argc, char *argv[], char ***my_envp)
{
	if (strcmp("echo", argv[1]) == 0 || strcmp("/usr/bin/echo", argv[1]) == 0 || strcmp("/bin/echo", argv[1]) == 0)
		ft_echo(argv);
	else if (strcmp("pwd", argv[1]) == 0)
		ft_pwd(argv);
	else if (strcmp("cd", argv[2]) == 0)
		ft_cd(argv);
	else if (strcmp("env", argv[1]) == 0)
		ft_env(argv, *my_envp, 1);
	else if (strcmp("export", argv[1]) == 0)
		*my_envp = export_init(argc, argv, *my_envp);
	else if (strcmp("unset", argv[1]) == 0)
	    ft_unset(*my_envp, argv[2]);
	// else if (strcmp("exit", argv[1]) == 0)
	//     ft_exit(envp, 1);
	else
		return(0);
	return(1);
}

// int	main(int argc, char *argv[], char **envp)
// {
// 	char **my_envp = ft_double_strdup(envp);
// 	if (argc == 1)
// 		return (1);
// 	determine_builtin(argc, argv, &my_envp);
// /* 	int i = 0;
// 	while (my_envp[i])
// 	{
// 		printf("%s\n", my_envp[i]);
// 		i++;
// 	} */
// 	t_hell	*data;
// 	int		i;
// 	if (determine_builtin(argv, envp) == 1)
// 		return(0);
// 	data = malloc(sizeof(t_hell));
// 	if (!data)
// 		exit(errno);
// 	cmd_init(argc, argv, data);
// 	cmd_exec(data, argv, envp);
// 	ft_freedata(data->cmd);
// 	free(data->path);
// 	free(data);
// 	ft_freedata(my_envp);
// }
