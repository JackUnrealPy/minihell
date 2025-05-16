#include "../../includes/minishell.h"

void	ft_cd(t_hell *hell, t_proc *head)
{
	char	old[PATH_MAX];
	char	current[PATH_MAX];
	char	*tmp;
	char	*pwd;
	char	*old_pwd;
	int		error_check;

	tmp = NULL;
	if (head->cmd[1] && head->cmd[2])
		return (error_msg(hell, NULL, "bash: cd: too many arguments", 1));
	old_pwd = ft_strjoin("OLDPWD=", getcwd(old, sizeof(old)));
	if (!head->cmd[1])
		error_check = chdir(getenv("HOME"));
	else if (head->cmd[1] && head->cmd[1][0] == '-')
	{
		tmp = ft_getenv("OLDPWD", hell->envp);
		error_check = chdir(tmp);
		free(tmp);
        ft_putendl_fd(getcwd(current, sizeof(current)), 1);
	}
	else
		error_check = chdir(head->cmd[1]);
	if (error_check)
	{
		ft_putstr_fd("bash: cd: ", 2);
		error_msg(hell, head->cmd[1], ": No such file or directory", 1);
		free(old_pwd);
		return ;
	}
	pwd = ft_strjoin("PWD=", getcwd(current, sizeof(current)));
	hell->envp = (char **)ft_mallocarr(hell, hell->freeme, (void **)ft_realloc_envp(hell->envp, 1, pwd));
	hell->envp = (char **)ft_mallocarr(hell, hell->freeme, (void **)ft_realloc_envp(hell->envp, 1, old_pwd));
	free(pwd);
	free(old_pwd);
}
