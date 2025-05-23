/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 04:19:15 by marvin            #+#    #+#             */
/*   Updated: 2025/05/20 04:19:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <linux/limits.h>

int	ft_pwd(t_hell *hell, t_redir *redirs, int pipe)
{
	int		fd;
	char	*success;

	fd = 1;
	if (!pipe)
	{
		while (redirs)
		{
			if (redirs->type == 1)
				fd = open(redirs->pathordel, O_CREAT | O_WRONLY | O_TRUNC,
						0644);
			else if (redirs->type == 2)
				fd = open(redirs->pathordel, O_CREAT | O_WRONLY | O_APPEND,
						0644);
			redirs = redirs->next;
		}
	}
	success = NULL;
	success = ft_getenv("PWD", hell->envp, 0);
	ft_putendl_fd(success, fd);
	free(success);
	if (fd != 1)
		close(fd);
	return (1);
}
