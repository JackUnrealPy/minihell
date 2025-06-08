/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:50:23 by agara             #+#    #+#             */
/*   Updated: 2025/06/08 16:53:55 by nrumpfhu         ###   ########.fr       */
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

void	**ft_mallocarr(t_hell *hell, t_free **head, void **obj)
{
	int	i;

	ft_malloc(hell, head, obj);
	i = -1;
	while (obj[++i])
		ft_malloc(hell, head, obj[i]);
	return (obj);
}

void	*ft_malloc(t_hell *hell, t_free **head, void *obj)
{
	t_free	*new;

	if (!obj)
		jump_ship(hell, 1);
	new = malloc(sizeof(t_free));
	if (!new)
	{
		ft_terminate(1, &obj);
		jump_ship(hell, 1);
	}
	new->freeme = obj;
	new->next = NULL;
	add_garbage(head, new);
	return (obj);
}
