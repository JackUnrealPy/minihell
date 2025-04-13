#include "../../includes/minishell.h"

int	determine_builtin(t_hell *hell, t_proc *head, char **cmd, int pipe)
{
	if (ft_strncmp(head->cmd[0], "echo", ft_strlen(head->cmd[0])) == 0 || ft_strncmp("/usr/bin/echo", head->cmd[0], ft_strlen(head->cmd[0])) == 0 || ft_strncmp("/bin/echo", head->cmd[0], ft_strlen(head->cmd[0])) == 0)
		ft_echo(head, pipe);
	else if (strcmp("pwd", head->cmd[0]) == 0)
		ft_pwd(*(head->redirs), pipe);
	// else if (strcmp("cd", head->cmd[0]) == 0)
	// 	ft_cd(hell);
	else if (strcmp("env", head->cmd[0]) == 0)
		ft_env((*head->redirs), hell->envp, pipe);
	// else if (strcmp("export", head->cmd[0]) == 0)
	// 	export_init(hell, hell->envp);
	else if (ft_strncmp("unset", head->cmd[0], ft_strlen(head->cmd[0])) == 0)
	    ft_unset(hell->envp, head->cmd[1]);
	else if (ft_strncmp("exit", head->cmd[0], ft_strlen(head->cmd[0])) == 0)
	    ft_exit(hell, head, cmd, pipe);
	else
		return(0);
	return(1);
}