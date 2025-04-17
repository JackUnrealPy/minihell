/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:49:56 by agara             #+#    #+#             */
/*   Updated: 2025/04/17 01:31:58 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	local_init(t_hell *hell, char *cmd)
{
	t_proc	*proc;
	(void)cmd;
	proc = create_proc(hell);
	*(hell->head) = proc;
}

void	env_init(t_hell *hell, char **envp)
{
	hell->test = ft_double_strdup(hell, envp, NULL);
	if (hell->exec_error)
	{
		free(hell->freeme);
		exit(1);
	}
    hell->envp = (char **)ft_mallocarr(hell, hell->freeme, (void **)hell->test);
}

int	init(t_hell *hell, char **envp)
{
	t_proc	**node;

	hell->lastexit = 0;
	hell->exec_error = 0;
	hell->freeme = malloc(sizeof(t_free *));
    (*hell->freeme) = NULL;
	env_init(hell, envp);
	node = malloc(sizeof(t_proc*)); 
	if (!node)
	{
		ft_terminate(1, &(hell->freeme));
		exit (1);
	}
	hell->head = node;
	return (1);
}
