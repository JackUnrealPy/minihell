#include "../../includes/minishell.h"

// void    update_env(t_hell *hell, char **envp, char *key, char *value)
// {
//     int i = 0;
//     while (envp[i])
//     {
//         if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0) // && envp[i][ft_strlen(key)+1] == '=')
//         {
//             printf("%s\n", envp[i]+ft_strlen(key)+1);
//             if (ft_strncmp(envp[i]+ft_strlen(key), value, ft_strlen(value)))
//                 printf("sir");
//         }
//         i++;
//     }
//     (void)hell;
// }

void	ft_cd(t_hell *hell, t_proc *head, char **cmd)
{
    // update_env(hell, hell->envp, "zz", "hello1");
    // return ;
    if (!head->cmd[1])
        chdir(getenv("HOME")); // go home -> figure out how
    else if (head->cmd[1][0] == '-')
    {
        chdir(getenv("OLDPWD"));
        // pwd = oldpwd;
        // oldpwd = pwd;
    }
	else if (chdir(head->cmd[1]) != 0)
    {
        // oldpwd = pwd
        // pwd = getpwd
        ft_putstr_fd("cd: ", 2);
        ft_putstr_fd(head->cmd[1], 2);
		error_msg(hell, cmd, ": No such file or directory", 1);
    }
    (void)cmd;
    (void)hell;
}

// change PWD and OLDPWD in envp