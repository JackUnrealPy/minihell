#include "builtins.h"

int	determine_builtin(char *argv[], char **envp)
{
	if (strcmp("echo", argv[0]) == 0 || strcmp("/usr/bin/echo", argv[0]) == 0 || strcmp("/bin/echo", argv[0]) == 0)
		ft_echo(argv);
	else if (strcmp("pwd", argv[0]) == 0)
		ft_pwd(argv);
	else if (strcmp("cd", argv[0]) == 0)
		ft_cd(argv);
	else if (strcmp("env", argv[0]) == 0)
		ft_env(envp, 1);
	else if (strcmp("export", argv[0]) == 0)
		ft_export(envp);
	// else if (strcmp("unset", argv[1]) == 0)
	//     ft_unset(argv);
	// else if (strcmp("exit", argv[1]) == 0)
	//     ft_exit(envp, 1);
	else
		return(0);
	return(1);
}

// int	main(int argc, char *argv[], char **envp)
// {
// 	if (argc == 1)
// 		return (1);
// 	determine_builtin(argv, envp);
// }
