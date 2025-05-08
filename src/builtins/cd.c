#include "../../includes/minishell.h"

void	ft_cd(t_hell *hell, t_proc *head, char **cmd)
{
	if (chdir(head->cmd[1]) != 0)
    {
        ft_putstr_fd("cd: ", 2);
        ft_putstr_fd(head->cmd[1], 2);
		error_msg(hell, cmd, ": No such file or directory", 1);
    }
    (void)cmd;
    (void)hell;
}

// change working directory
// change PWD in envp
// change path in terminal