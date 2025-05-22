/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:49:56 by agara             #+#    #+#             */
/*   Updated: 2025/05/17 21:55:20 by nrumpfhu         ###   ########.fr       */
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

void init_hell(t_hell *hell, char **envp)
{
	char pwd[PATH_MAX];
	char *pwd_env = NULL;
	char *env;
	if (!envp[0])
	{
		getcwd(pwd, sizeof(pwd));
		pwd_env = ft_strjoin("PWD=", pwd);
		env = ft_strjoin(pwd_env, "\nSHLVL=1\n_=/usr/bin/env");
		hell->envp = (char **)ft_mallocarr(hell, hell->freeme, (void **)ft_split(env, "\n"));
		free(pwd_env);
		free(env);
	}
	else
		hell->envp = (char **)ft_mallocarr(hell, hell->freeme, (void **)ft_double_strdup(hell, envp));
}

int	init(t_hell *hell, char **envp)
{
	t_proc	**node;

	hell->lastexit = 0;
	hell->syntaxerr = 0;
	hell->exec_error = 0;
	hell->freeme = malloc(sizeof(t_free *));
    (*hell->freeme) = NULL;
	init_hell(hell, envp);
	node = malloc(sizeof(t_proc*)); 
	if (!node)
	{
		ft_terminate(1, &(hell->freeme));
		exit (1);
	}
	hell->head = node;
	return (1);
}