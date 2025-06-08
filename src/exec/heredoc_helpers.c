/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 04:18:28 by marvin            #+#    #+#             */
/*   Updated: 2025/06/08 22:32:41 by nrumpfhu         ###   ########.fr       */
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

void	expand_heredoc(t_hell *hell, t_proc *head, char **buffer, int pos)
{
	char	*val;
	char	*res;
	int		j;

	j = 0;
	val = get_exp(hell, head, *buffer, &j);
	res = ft_calloc(sizeof(char), ft_strlen(*buffer) - j + ft_strlen(val) + 1);
	if (!res)
		jump_ship(hell, 1);
	ft_memcpy(res, *buffer, pos);
	ft_memcpy(res + pos, val, ft_strlen(val));
	ft_memcpy(res + ft_strlen(val) + pos,
		*buffer + pos + j,
		ft_strlen(*buffer + pos) - j);
	pop_free(head->freeme, *buffer);
	*buffer = res;
}

void	expansion_heredoc(t_hell *hell, t_proc *head, char **buffer)
{
	int		i;

	if (*buffer && (*head->redirs)->type == 4)
	{
		i = 0;
		while ((*buffer)[i])
		{
			if ((*buffer)[i] == '$')
			{
				expand_heredoc(hell, head, buffer, i);
				break ;
			}
			i++;
		}
	}
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
		buffer = NULL;
		return (1);
	}
	return (0);
}
