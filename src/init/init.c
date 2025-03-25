/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:49:56 by agara             #+#    #+#             */
/*   Updated: 2025/03/25 18:59:22 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	local_init(t_hell *hell, char *cmd)
{
	t_proc	*proc;

	proc = create_proc(hell);
	*(hell->head) = proc;
	// proc->input = ft_malloc(proc->freeme, ft_strdup(cmd));
}

int	init(t_hell *hell, char **envp)
{
	t_proc	**node;

	hell->freeme = NULL;
	hell->envp = envp;
	node = malloc(sizeof(t_proc*)); 
	if (!node)
	{
		ft_terminate(1, &(hell->freeme));
		exit (1);
	}
	hell->head = node;
	return (1);
}