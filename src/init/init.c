/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:49:56 by agara             #+#    #+#             */
/*   Updated: 2025/04/14 21:28:40 by nrumpfhu         ###   ########.fr       */
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

int	init(t_hell *hell, char **envp)
{
	t_proc	**node;

	hell->freeme = malloc(sizeof(t_free *));
    (*hell->freeme) = NULL;
	hell->lastexit = malloc(sizeof(int));
	(*hell->lastexit) = 0;
	hell->test = ft_double_strdup(hell, envp, NULL);
    hell->envp = (char **)ft_mallocarr(hell, hell->freeme, (void **)hell->test); // not properly freed for cmd "echo hello | cat -e" -> any pipes involving builtins for some reason
	node = malloc(sizeof(t_proc*)); 
	if (!node)
	{
		ft_terminate(1, &(hell->freeme));
		exit (1);
	}
	hell->head = node;
	return (1);
}
