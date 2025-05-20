/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 04:18:28 by marvin            #+#    #+#             */
/*   Updated: 2025/05/20 04:18:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	generate_tmpfile(t_hell *hell, t_proc *head)
{
	char	rando_txt[10];
	char	rando_char;
	int		i;
	int		fd;

	(void)hell;
	i = 0;
	fd = open("/dev/urandom", O_RDONLY);
	while (i < 9)
	{
		read(fd, &rando_char, 1);
		if (ft_isalnum(rando_char))
			rando_txt[i++] = rando_char;
	}
	close(fd);
	rando_txt[9] = 0;
	head->hdoc_tmpfile = ft_malloc(hell, hell->freeme, ft_strjoin("/tmp/.",
				rando_txt));
}

void	expansion_heredoc(t_hell *hell, t_proc *head, char *buffer, char *tmp)
{
	int	i;

	if (buffer && (*head->redirs)->type == 4)
	{
		i = 0;
		while (buffer[i])
		{
			if (buffer[i] == '$')
			{
				tmp = buffer;
				buffer = ft_strchr(buffer, '$');
				ft_expand(hell, head, &buffer, 0);
				break ;
			}
			i++;
		}
	}
	(void)tmp;
}

int	break_heredoc(t_redir *redirs, char *buffer)
{
	if (!buffer)
	{
		ft_putstr_fd("Warning: here-document delimited by EOF\n", 2);
		return (1);
	}
	if (ft_strlen(buffer) == ft_strlen(redirs->pathordel) && ft_strncmp(buffer,
			redirs->pathordel, ft_strlen(redirs->pathordel)) == 0)
	{
		free(buffer);
		return (1);
	}
	return (0);
}
