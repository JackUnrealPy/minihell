/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 04:17:46 by marvin            #+#    #+#             */
/*   Updated: 2025/06/08 17:43:51 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	try_paths(t_hell *hell, t_proc *head, char **path, char *path_cmd)
{
	char	*test_path;
	int		i;

	test_path = NULL;
	i = 0;
	while (path && path[i])
	{
		test_path = ft_strjoin(path[i], path_cmd);
		if (!test_path)
			jump_ship(hell, 1);
		if (access(test_path, R_OK | X_OK) == 0)
		{
			head->cmd_path = ft_malloc(hell, head->freeme, test_path);
			break ;
		}
		free(test_path);
		test_path = NULL;
		i++;
	}
}

void	test_cmds(t_hell *hell, t_proc *head)
{
	char	*env_check;
	char	*path_env;
	char	**path;
	char	*path_cmd;

	path_env = NULL;
	env_check = ft_getenv("PATH", hell->envp, 0);
	if (!env_check)
		return (error_msg(hell, head->cmd[0], ": No such file or directory",
				127));
	path_env = ft_malloc(hell, head->freeme, env_check);
	if (!path_env || !path_env[0])
		return (error_msg(hell, head->cmd[0], ": No such file or directory",
				127));
	path = (char **)ft_mallocarr(hell, head->freeme, (void **)ft_split(path_env,
				":"));
	if (!path)
		return (error_msg(hell, NULL, "Memory allocation failed", 1));
	path_cmd = ft_malloc(hell, head->freeme, ft_strjoin("/", head->cmd[0]));
	try_paths(hell, head, path, path_cmd);
	if (!head->cmd_path)
		head->cmd_path = head->cmd[0];
}

void	increment_shlvl(char **envp)
{
	int		i;
	char	*shlvl;
	char	*new_shlvl;

	i = 0;
	shlvl = ft_getenv("SHLVL", envp, 0);
	new_shlvl = ft_strjoin("SHLVL=", ft_itoa((ft_atoi(shlvl) + 1)));
	while (envp[i])
	{
		if (envp[i] && ft_strncmp(envp[i], "SHLVL=", 6) == 0)
		{
			free(envp[i]);
			envp[i] = NULL;
			envp[i] = ft_strdup(new_shlvl);
			break ;
		}
		i++;
	}
	free(shlvl);
	free(new_shlvl);
}

void	create_cmd(t_hell *hell, t_proc *head)
{
	head->cmd_path = NULL;
	if (!head->cmd)
		return ;
	else if (ft_strchr(head->cmd[0], '/'))
	{
		head->cmd_path = ft_malloc(hell, head->freeme, ft_strdup(head->cmd[0]));
		if (ft_strncmp(head->cmd[0], "./minishell", 11) == 0)
			increment_shlvl(hell->envp);
		if (access(head->cmd_path, F_OK) == -1)
			error_msg(hell, head->cmd[0], ": No such file or directory", 1);
		return ;
	}
	else
	{
		test_cmds(hell, head);
		if (hell->exec_error)
			return ;
	}
}
