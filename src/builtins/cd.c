/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 04:18:53 by marvin            #+#    #+#             */
/*   Updated: 2025/06/08 17:17:18 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// add cd ~/whatever
int	cd_home(t_hell *hell, char *cmd1)
{
	char	*home;
	int		ret;
	char	*new_dir;

	ret = 0;
	home = ft_getenv("HOME", hell->envp, 0);
	if (!home)
		return (free(home), error_msg(hell, NULL, "minishell: cd: HOME not set",
				1), 1);
	if (cmd1 && ft_strlen(cmd1) > 1)
	{
		new_dir = ft_strjoin(home, cmd1 + 1);
		ret = chdir(new_dir);
		free(new_dir);
	}
	else
		ret = chdir(home);
	free(home);
	return (ret);
}

int	cd_oldpwd(t_hell *hell)
{
	char	*oldpwd;
	char	current[PATH_MAX];
	int		ret;

	ret = 0;
	oldpwd = ft_getenv("OLDPWD", hell->envp, 0);
	if (!oldpwd)
		return (free(oldpwd), error_msg(hell, NULL, "cd: OLDPWD not set", 1),
			1);
	ret = chdir(oldpwd);
	free(oldpwd);
	if (!ret)
		return (ft_putendl_fd(getcwd(current, sizeof(current)), 1), 0);
	return (1);
}

void	cd_update_vars(t_hell *hell, t_proc *head, char *old_pwd)
{
	char	current[PATH_MAX];
	char	*old;
	char	*pwd;
	char	*pwd_arr[2];
	char	*old_arr[2];

	(void)head;
	getcwd(current, sizeof(current));
	pwd = ft_strjoin("PWD=", current);
	old = ft_strjoin("OLDPWD=", old_pwd);
	pwd_arr[0] = pwd;
	pwd_arr[1] = NULL;
	old_arr[0] = old;
	old_arr[1] = NULL;
	hell->envp = (char **)ft_mallocarr(hell, hell->freeme,
			(void **)ft_realloc_envp(hell->envp, 1, pwd_arr));
	hell->envp = (char **)ft_mallocarr(hell, hell->freeme,
			(void **)ft_realloc_envp(hell->envp, 1, old_arr));
	free(pwd);
	free(old);
	free(old_pwd);
}

void	ft_cd(t_hell *hell, t_proc *head)
{
	char	*old_pwd;
	int		error_check;

	error_check = 0;
	if (head->cmd[1] && head->cmd[2])
		return (error_msg(hell, NULL, "minishell: cd: too many arguments", 1));
	old_pwd = ft_getenv("PWD", hell->envp, 0);
	if (!head->cmd[1] || head->cmd[1][0] == '~')
		error_check = cd_home(hell, head->cmd[1]);
	else if (head->cmd[1] && head->cmd[1][0] == '-')
		error_check = cd_oldpwd(hell);
	else
		error_check = chdir(head->cmd[1]);
	if (error_check)
	{
		free(old_pwd);
		if (error_check > 0)
			return ;
		ft_putstr_fd("minishell: cd: ", 2);
		error_msg(hell, head->cmd[1], ": No such file or directory", 1);
		return ;
	}
	cd_update_vars(hell, head, old_pwd);
}
