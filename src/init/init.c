/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:49:56 by agara             #+#    #+#             */
/*   Updated: 2025/03/19 20:55:36 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_proc	*create_proc(const char *cmd)
{
	t_proc	*proc;
	
	proc = malloc(sizeof(t_proc));
	if (!proc)
		exit(1);
	proc->prev = NULL;
	proc->input = ft_strdup(cmd);
	if (!proc->input)
		exit(1);
	proc->next = NULL;
	return (proc);
}

int	init(t_hell *hell, char **envp)
{
	// t_free	*free;


	// free = malloc(sizeof(t_free));
	// if (!free)
	// 	exit(1);
	// hell->freeme = free;
	hell->envp = envp;
	
	hell->head = NULL; 
	
	return (1);
}