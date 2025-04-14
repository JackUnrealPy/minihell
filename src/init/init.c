/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:49:56 by agara             #+#    #+#             */
/*   Updated: 2025/03/28 15:33:04 by agara            ###   ########.fr       */
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

	hell->freeme = NULL;
	hell->lastexit = 0;
	hell->envp = envp;
	hell->localvars = NULL;
	node = malloc(sizeof(t_proc*)); 
	if (!node)
		exit (1);
	hell->head = node;
	return (1);
}