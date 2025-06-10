/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealloc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:43:10 by agara             #+#    #+#             */
/*   Updated: 2025/06/10 13:43:11 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	throw_garbage(t_free **head)
{
	t_free	*tempnext;
	t_free	*node;

	if (!head)
		return ;
	node = *head;
	while (node)
	{
		tempnext = node->next;
		ft_terminate(1, &(node->freeme));
		ft_terminate(1, &node);
		node = tempnext;
	}
	ft_terminate(1, &head);
}

void	del_token(t_token **tokens, t_token *token)
{
	t_token	*next;
	t_token	*prev;

	if (!*tokens || !token)
		return ;
	next = token->next;
	prev = token->prev;
	if (next)
		next->prev = prev;
	if (prev)
		prev->next = next;
	else
		*tokens = next;
	ft_terminate(1, &(token->token));
	ft_terminate(1, &(token->expansion));
	ft_terminate(1, &token);
}

void	pop_free(t_free **head, void *ptr)
{
	t_free	*node;
	t_free	*prev;

	node = *head;
	prev = NULL;
	while (node)
	{
		if (node->freeme == ptr)
		{
			prev->next = node->next;
			ft_terminate(1, &(node->freeme));
			ft_terminate(1, &node);
			return ;
		}
		prev = node;
		node = node->next;
	}
}

void	pop_token(t_token **head, void *ptr, int all)
{
	t_token	*node;
	t_token	*next;

	if (!head || !*head)
		return ;
	node = *head;
	while (node)
	{
		next = node->next;
		if (all)
			del_token(head, node);
		else if (node->token == ptr)
		{
			del_token(head, node);
			return ;
		}
		node = next;
	}
}
