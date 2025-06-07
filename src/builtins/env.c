/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 04:19:03 by marvin            #+#    #+#             */
/*   Updated: 2025/06/07 17:49:29 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_redir *redirs, char **envp, int pipe)
{
	int		fd;
	t_redir	*redirs_cpy;
	int		i;

	fd = 1;
	redirs_cpy = redirs;
	if (!pipe)
	{
		while (redirs_cpy)
		{
			if (redirs_cpy->type == 1)
				fd = open(redirs_cpy->pathordel, O_CREAT | O_WRONLY | O_TRUNC,
						0644);
			else if (redirs_cpy->type == 2)
				fd = open(redirs_cpy->pathordel, O_CREAT | O_WRONLY | O_APPEND,
						0644);
			redirs_cpy = redirs_cpy->next;
		}
	}
	i = -1;
	while (envp[++i])
	{
		if (ft_strchr(envp[i], '='))
			ft_putendl_fd(envp[i], fd);
	}
	if (fd != 1)
		close(fd);
	return (0);
}
