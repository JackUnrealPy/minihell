/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 04:18:22 by marvin            #+#    #+#             */
/*   Updated: 2025/05/20 04:18:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	loop_cmds(t_hell *hell)
{
	if ((*hell->head) && !(*hell->head)->next)
		single_cmd(hell, (*hell->head));
	else if ((*hell->head) && (*hell->head)->next)
		ft_pipex(hell);
	return (0);
}
