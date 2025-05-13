#include "../../includes/minishell.h"

int is_builtin(t_proc *head)
{
	if (!head->cmd)
		return(0);
	else if (strcmp(head->cmd[0], "echo") | strcmp(head->cmd[0], "pwd") | strcmp(head->cmd[0], "cd") | strcmp(head->cmd[0], "env") | strcmp(head->cmd[0], "export") | strcmp(head->cmd[0], "unset") | strcmp(head->cmd[0], "exit"))
		return (1);
	else
		return (0);
}

// add ft_strcmp to libft and change functions here
int	determine_builtin(t_hell *hell, t_proc *head, char **cmd, int pipe)
{
	if (!head->cmd)
		return (0);
	else if (ft_strncmp(head->cmd[0], "echo", ft_strlen(head->cmd[0])) == 0)
		ft_echo(hell, head, cmd, pipe);
	else if (strcmp("pwd", head->cmd[0]) == 0)
		ft_pwd(*(head->redirs), pipe);
	else if (strcmp("cd", head->cmd[0]) == 0)
		ft_cd(hell, head, cmd);
	else if (strcmp("env", head->cmd[0]) == 0)
		ft_env((*head->redirs), hell->envp, pipe);
	else if (strcmp("export", head->cmd[0]) == 0)
		ft_export(hell, head, cmd);
	else if (ft_strncmp("unset", head->cmd[0], ft_strlen(head->cmd[0])) == 0)
		ft_unset(hell, hell->envp, head->cmd[1]);
	else if (ft_strncmp("exit", head->cmd[0], ft_strlen(head->cmd[0])) == 0)
		ft_exit(hell, head, cmd, pipe);
	else
		return(0);
	if (!hell->exec_error)
		hell->lastexit = 0;
	return (1);

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
			return (0);
		}
		redirs_cpy = redirs_cpy->next;
	}
	hell->lastexit = 0;
	return(fd);
}