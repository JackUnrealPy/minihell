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
	char old[PATH_MAX];
    char current[PATH_MAX];
    char *pwd;
    char *old_pwd;
    int error_check;
    // update_env(hell, hell->envp, "zz", "hello1");
    // return ;
    if (head->cmd[1] && head->cmd[2])
    {
		error_msg(hell, cmd, "bash: cd: too many arguments", 1);
        return ;
    }
    old_pwd = ft_strjoin("OLDPWD=", getcwd(old, sizeof(old)));
    if (!head->cmd[1])
    {
       error_check = chdir(ft_getenv("HOME", hell->envp));
        
    }
    else if (head->cmd[1] && (head->cmd[1][0] == '-' || head->cmd[1][0] == '-'))
    {
       error_check = chdir(ft_getenv("OLDPWD", hell->envp));
       if (head->cmd[1][0] == '-')
            ft_putendl_fd(getcwd(current, sizeof(current)), 1);
    }
    else
       error_check = chdir(head->cmd[1]);
    if (error_check)
    {
        ft_putstr_fd("bash: cd: ", 2);
        ft_putstr_fd(head->cmd[1], 2);
		error_msg(hell, cmd, ": No such file or directory", 1);
        free(old_pwd);
        return; // free
    }
    pwd = ft_strjoin("PWD=", getcwd(current, sizeof(current))); // rewrite ft_getenv to not use malloc
    hell->envp = (char **)ft_mallocarr(hell, hell->freeme, (void **)ft_realloc_envp(hell->envp, 1, pwd));

    hell->envp = (char **)ft_mallocarr(hell, hell->freeme, (void **)ft_realloc_envp(hell->envp, 1, old_pwd));
    free(pwd);
    free(old_pwd);
    (void)cmd;
    (void)hell;
}

// change PWD and OLDPWD in envp