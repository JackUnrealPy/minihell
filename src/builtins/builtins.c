#include "../../includes/minishell.h"

int	determine_builtin(t_hell *hell, t_proc *head, char **cmd, int pipe)
{
	if (head->cmd && (ft_strncmp(head->cmd[0], "echo", ft_strlen(head->cmd[0])) == 0 || ft_strncmp("/usr/bin/echo", head->cmd[0], ft_strlen(head->cmd[0])) == 0 || ft_strncmp("/bin/echo", head->cmd[0], ft_strlen(head->cmd[0])) == 0))
		ft_echo(hell, head, cmd, pipe);
	else if (head->cmd && strcmp("pwd", head->cmd[0]) == 0)
		ft_pwd(*(head->redirs), pipe);
	// else if (head->cmd && strcmp("cd", head->cmd[0]) == 0)
	// 	ft_cd(hell);
	else if (head->cmd && strcmp("env", head->cmd[0]) == 0)
		ft_env((*head->redirs), hell->envp, pipe);
	else if (head->cmd && strcmp("export", head->cmd[0]) == 0)
		ft_export(hell, head, cmd);
	else if (head->cmd && ft_strncmp("unset", head->cmd[0], ft_strlen(head->cmd[0])) == 0)
	    ft_unset(hell->envp, head->cmd[1]);
	else if (head->cmd && ft_strncmp("exit", head->cmd[0], ft_strlen(head->cmd[0])) == 0)
	    ft_exit(hell, head, cmd, pipe);
	else
		return(0);
	return(1);
}

int	builtins_output(t_hell *hell, t_proc *head, char **cmd)
{
	int fd = 1;
	t_redir *redirs_cpy = (*head->redirs);
	while (redirs_cpy)
	{
		if (redirs_cpy->type == 1)
			fd = open(redirs_cpy->pathordel, \
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (redirs_cpy->type == 2)
			fd = open(redirs_cpy->pathordel, \
			O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
		{
			ft_putstr_fd(redirs_cpy->pathordel, 2);
			error_msg(hell, cmd, ": permission denied", 1);
		}
		redirs_cpy = redirs_cpy->next;
	}
	return(fd);
}