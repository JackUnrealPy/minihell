#include "../../includes/minishell.h"



// add cd ~/whatever
int	cd_home(t_hell *hell)
{
	char *home;
	// char *tilde;
	int ret = 0;
	home = ft_getenv("HOME", hell->envp, 0);
	if (!home)
		return (free(home), error_msg(hell, NULL, "cd: HOME not set", 1), 1);
	ret = chdir(home);
	free(home);
	return(ret);
}

int	cd_oldpwd(t_hell *hell)
{
	char *oldpwd;
	char	current[PATH_MAX];
	int ret = 0;
	oldpwd = ft_getenv("OLDPWD", hell->envp, 0);
	if (!oldpwd)
		return (free(oldpwd), error_msg(hell, NULL, "cd: OLDPWD not set", 1), 1);
	ret = chdir(oldpwd);
	free(oldpwd);
	if (!ret)
		return (ft_putendl_fd(getcwd(current, sizeof(current)), 1), 0);
	return (1);
	// home = ft_getenv("HOME", hell->envp);
	// if (!home)
	// 	return (free(home), error_msg(hell, NULL, "cd: OLDPWD not set", 1), 0);
	// ret = chdir(home);
	// free(home);
	// return(ret);
}

void	ft_cd(t_hell *hell, t_proc *head)
{
	// char	old[PATH_MAX];
	char	*pwd;
	char	*old_pwd;
	int		error_check = 0;
	
	if (head->cmd[1] && head->cmd[2])
		return (error_msg(hell, NULL, "bash: cd: too many arguments", 1));
	old_pwd = ft_getenv("PWD", hell->envp, 0); // free ft_getenv
	if (!head->cmd[1] || head->cmd[1][0] == '~')
		error_check = cd_home(hell);
	else if (head->cmd[1] && head->cmd[1][0] == '-')
		error_check = cd_oldpwd(hell);
	else
		error_check = chdir(head->cmd[1]);
	if (error_check)
	{
		if (error_check > 0)
			return ;
		ft_putstr_fd("bash: cd: ", 2);
		error_msg(hell, head->cmd[1], ": No such file or directory", 1);
		return ;
	}
	char current[PATH_MAX];
	char *cur;
	if (!head->cmd[1] || (head->cmd[1] && (ft_strchr(head->cmd[1], '.') || head->cmd[1][0] == '/')))
	{
		getcwd(current, sizeof(current));
		if (head->cmd[1] && head->cmd[1][0] != '/')
		{
			cur = ft_strjoin(current, head->cmd[1]);
			pwd = ft_strjoin("PWD=", cur);
		}
		else
			pwd = ft_strjoin("PWD=", current);
	}
	else
	{
		ft_strlcpy(current, head->cmd[1], ft_strlen(head->cmd[1]));
		pwd = ft_strjoin("PWD=", current);
	}
	pwd = ft_strjoin("PWD=", current);  //ft_getenv("PWD", hell->envp, 1);
	char *old = ft_strjoin("OLDPWD=", old_pwd);
	hell->envp = (char **)ft_mallocarr(hell, hell->freeme, (void **)ft_realloc_envp(hell->envp, 1, pwd));
	// exit(0);
	hell->envp = (char **)ft_mallocarr(hell, hell->freeme, (void **)ft_realloc_envp(hell->envp, 1, old));
}
