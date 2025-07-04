/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 04:18:22 by marvin            #+#    #+#             */
/*   Updated: 2025/06/11 13:10:10 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	loop_cmds(t_hell *hell)
{
	hell->hdoc_sig = 0;
	if ((*hell->head) && !(*hell->head)->next)
		single_cmd(hell, (*hell->head));
	else if ((*hell->head) && (*hell->head)->next)
		ft_pipex(hell);
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
