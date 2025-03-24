#include "../../includes/minishell.h"
#include <string.h>

void	ft_echo(t_proc *head, int pipe);
int	ft_env(t_redir *redirs, char **envp, int pipe);
int	ft_pwd(t_redir *redirs, int pipe);

int	determine_builtin(t_hell *hell, t_proc *head, int pipe)
{
	if (ft_strncmp(head->cmd[0], "echo", ft_strlen(head->cmd[0])) == 0 || ft_strncmp("/usr/bin/echo", head->cmd[0], ft_strlen(head->cmd[0])) == 0 || ft_strncmp("/bin/echo", head->cmd[0], ft_strlen(head->cmd[0])) == 0)
		ft_echo((*hell->head), pipe);
	else if (strcmp("pwd", head->cmd[0]) == 0)
		ft_pwd(head->redirs, pipe);
	// else if (strcmp("cd", head->cmd[0]) == 0)
	// 	ft_cd(hell);
	else if (strcmp("env", head->cmd[0]) == 0)
		ft_env((*hell->head)->redirs, hell->envp, pipe);
	// else if (strcmp("export", head->cmd[0]) == 0)
	// 	export_init(hell, hell->envp);
	// else if (strcmp("unset", head->cmd[0]) == 0)
	//     ft_unset(hell->envp, (*hell->head), pipe);
	// else if (strcmp("exit", head->cmd[0]) == 0)
	//     ft_exit(envp, 1);
	else
		return(0);
	return(1);
}
