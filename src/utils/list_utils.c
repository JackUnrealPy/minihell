/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:42:48 by agara             #+#    #+#             */
/*   Updated: 2025/06/10 13:42:49 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_list(t_proc *a)
{
	t_redir	*reds;
	int		i;

	while (a)
	{
		if (a->cmd && *(a->cmd))
		{
			i = -1;
			while (a->cmd[++i])
				printf("cmd [%d]:{%s}\n", i, a->cmd[i]);
		}
		reds = *(a->redirs);
		while (reds)
		{
			printf("reds [%d]:{%s}\n", reds->type, reds->pathordel);
			reds = reds->next;
		}
		a = a->next;
	}
}
