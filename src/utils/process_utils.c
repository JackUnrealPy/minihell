/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:50:23 by agara             #+#    #+#             */
/*   Updated: 2025/03/25 21:04:11 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	addproc(t_proc **head, t_proc *next)
{
	t_proc	*node;

	node = *head;
	while (node->next)
		node = node->next;
	next->prev = node;
	node->next = next;
}

t_proc	*create_proc(t_hell *hell)
{
	t_proc	*proc;
	t_free	**freeme;
	
	proc = malloc(sizeof(t_proc));
	if (!proc)
		jump_ship(hell, 1);
	freeme = malloc(sizeof(t_free*));
	if (!freeme)
	{
		ft_terminate(1, &proc);
		jump_ship(hell, 1);
	}
	proc->freeme = freeme;
	proc->cmd = NULL;
	*(proc->freeme) = NULL;
	proc->prev = NULL;
	proc->next = NULL;
	return (proc);
}

static void	ft_procclear(t_proc **proc)
{
	t_proc	*tempnext;
	t_proc	*node;

	if (!proc || !*proc)
		return ;
	node = *proc;
	while (node)
	{
		tempnext = node->next;
		ft_terminate(1, &node);
		node = tempnext;
	}
}

void	close_proc(t_hell *hell)
{
	t_proc	*proc;
	t_proc	*tmp;

	proc = *(hell->head);
	while (proc)
	{
		tmp = proc->next;
		throw_garbage(proc->freeme);
		proc = tmp;
	}
	ft_procclear(hell->head);
}