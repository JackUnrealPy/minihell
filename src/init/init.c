/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:49:56 by agara             #+#    #+#             */
/*   Updated: 2025/06/08 22:29:09 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	local_init(t_hell *hell, char *cmd)
{
	t_proc	*proc;

	(void)cmd;
	proc = create_proc(hell);
	*(hell->head) = proc;
	hell->exec_error = 0;
}

void	init_mem(t_hell *hell, char *pwd_env, char *env, char **split)
{
	ft_putstr_fd("Memory allocation failed\n", 2);
	if (hell->freeme)
		free(hell->freeme);
	if (pwd_env)
		free(pwd_env);
	if (env)
		free(env);
	if (split)
		free(split);
	exit(1);
}

void	empty_env(t_hell *hell)
{
	char	pwd[PATH_MAX];
	char	*pwd_env;
	char	*env;
	char	**split;

	pwd_env = NULL;
	env = NULL;
	split = NULL;
	getcwd(pwd, sizeof(pwd));
	pwd_env = ft_strjoin("OLDPWD\nPWD=", pwd);
	if (!pwd_env)
		init_mem(hell, pwd_env, env, split);
	env = ft_strjoin(pwd_env, "\nSHLVL=1\n_=/usr/bin/env");
	if (!env)
		init_mem(hell, pwd_env, env, split);
	split = ft_split(env, "\n");
	if (!split)
		init_mem(hell, pwd_env, env, split);
	hell->envp = (char **)ft_mallocarr(hell, hell->freeme, (void **)split);
	free(pwd_env);
	free(env);
}

void	init_hell(t_hell *hell, char **envp)
{
	char	**env;

	env = NULL;
	if (!getenv("PATH"))
		empty_env(hell);
	else
	{
		env = ft_double_strdup(hell, envp);
		if (!env)
			init_mem(hell, NULL, NULL, NULL);
		hell->envp = (char **)ft_mallocarr(hell, hell->freeme, (void **)env);
	}
}

int	init(t_hell *hell, char **envp)
{
	hell->lastexit = 0;
	hell->syntaxerr = 0;
	hell->exec_error = 0;
	hell->head = NULL;
	hell->freeme = NULL;
	hell->tokens = NULL;
	hell->freeme = malloc(sizeof(t_free *));
	if (!hell->freeme)
		exit(1);
	(*hell->freeme) = NULL;
	init_hell(hell, envp);
	hell->head = malloc(sizeof(t_proc *));
	if (!hell->head)
	{
		ft_freeme(hell->envp);
		free(hell->freeme);
		free(hell->head);
		ft_putstr_fd("Memory allocation failed\n", 2);
		exit(1);
	}
	return (1);
}
