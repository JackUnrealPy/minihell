/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:50:23 by agara             #+#    #+#             */
/*   Updated: 2025/03/22 21:15:41 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	add_garbage(t_free **head, t_free *node)
{
	t_free	*tmp;

	if (!(*head))
	{
		(*head) = node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

void	*ft_malloc(t_free **head, void *obj)
{
	t_free	*new;

	if (!obj)
		exit(1);
	new = malloc(sizeof(t_free));
	if (!new)
	{
		ft_terminate(1, &obj);
		exit(1);
	}
	new->freeme = obj;
	new->next = NULL;
	add_garbage(head, new);
	return (obj);
}

void	throw_garbage(t_free **head)
{
	t_free	*tempnext;
	t_free	*node;

	if (!head || !*head)
		return ;
	node = *head;
	while (node)
	{
		tempnext = node->next;
		ft_terminate(2, &(node->freeme), &node);
		node = tempnext;
	}
	ft_terminate(1, &head);
}
