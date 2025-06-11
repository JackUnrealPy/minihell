/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:50:23 by agara             #+#    #+#             */
/*   Updated: 2025/06/11 16:15:38 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_proc	*get_last_proc(t_proc **head)
{
	t_proc	*proc;

	proc = *head;
	while (proc->next)
		proc = proc->next;
	return (proc);
}

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

	proc = NULL;
	proc = malloc(sizeof(t_proc));
	if (!proc)
		jump_ship(hell, 1);
	proc->freeme = malloc(sizeof(t_free *));
	if (!proc->freeme)
	{
		ft_terminate(1, &proc);
		jump_ship(hell, 1);
	}
	*(proc->freeme) = NULL;
	proc->cmd = NULL;
	proc->prev = NULL;
	proc->next = NULL;
	proc->redirerr = 0;
	proc->redirs = ft_malloc(hell, proc->freeme, malloc(sizeof(t_redir *)));
	*(proc->redirs) = NULL;
	proc->tokens = malloc(sizeof(t_token *));
	if (!proc->tokens)
		jump_ship(hell, 1);
	*(proc->tokens) = NULL;
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
		pop_token(proc->tokens, NULL, 1);
		ft_terminate(1, &(proc->tokens));
		throw_garbage(proc->freeme);
		proc = tmp;
	}
	ft_terminate(1, &(hell->tokens));
	ft_procclear(hell->head);
}
