/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:39:23 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/06/12 17:52:09 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_fd(t_hell *hell, char *path, int redir_type)
{
	int	fd;

	if (redir_type == 1)
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir_type == 2)
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
	{
		if (access(path, F_OK) == -1)
			redirs_error(hell, path, ": No such file or directory", 1);
		fd = open(path, O_RDONLY, 0644);
	}
	return (fd);
}

int	is_directory(char *cmd)
{
	struct stat	buf;

	if (cmd[0] == '~' && (!cmd[1] || cmd[1] == '/'))
		return (1);
	if (stat(cmd, &buf) == 0 && S_ISDIR(buf.st_mode))
		return (1);
	return (0);
}

void	redirs_error(t_hell *hell, char *pathordel, char *msg, int errnum)
{
	error_msg(hell, pathordel, msg, errnum);
	jump_ship(hell, errnum);
}
