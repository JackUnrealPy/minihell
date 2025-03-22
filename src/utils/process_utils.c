/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:50:23 by agara             #+#    #+#             */
/*   Updated: 2025/03/22 19:53:27 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_procclear(t_proc **proc)
{
	t_proc	*tempnext;
	t_proc	*node;

	if (!proc || !*proc)
		return ;
	node = *proc;
	while (node)
	{
		tempnext = node->next;
		ft_terminate(2, &(node->input), &node);
		node = tempnext;
	}
}