/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:52:33 by agara             #+#    #+#             */
/*   Updated: 2025/04/23 20:07:41 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

static int	fill_redir(t_hell *hell, t_proc *proc, char *str, t_redir *new)
{
	int		i;
	int		j;
	int		qflag[2];
	
	i = 0;
	j = 0;
	while (str[j] && ft_isspace(str[j]))
		j++;
	while (str[j + i] && !ft_isspace(str[j + i]))
		i++;
	new->pathordel = ft_malloc(hell, proc->freeme, ft_calloc(i + 1, sizeof(char)));
	new->next = NULL;
	i = 0;
	qflag[0] = 0;
	qflag[1] = 0;
	while (str[j + i] && !ft_isspace(str[j + i]))
	{
		if (str[j + i] == '\'' && (qflag[1] % 2 == 0))
		{
			qflag[0]++;
			j++;
			continue ;
		}

		if (str[j + i] == '\"' && (qflag[0] % 2 == 0))
		{
			qflag[1]++;
			j++;
			continue ;
		}
		new->pathordel[i] = str[j + i];
		i++;
	}
	if (qflag[0] % 2 || qflag[1] % 2)
		sysntaxerr();
	if (new->type == 3 && !qflag[0] && !qflag[1])
		new->type = 4;
	return (i + j);
}

static t_redir	*create_redir(t_hell *hell, t_proc *proc, char *str, int *res)
{
	t_redir	*new;

	new = ft_malloc(hell, proc->freeme, malloc(sizeof(t_redir)));
	*res += 1;
	if (str[0] == '<' && str[1] == '<')
	{
		new->type = 3;
		*res += 1;
	}
	else if (str[0] == '>' && str[1] == '>')
	{
		new->type = 2;
		*res += 1;
	}
	else if (str[0] == '<')
		new->type = 0;
	else if (str[0] == '>')
		new->type = 1;
	*res += fill_redir(hell, proc, (str + (*res)), new);
	return (new);
}


int	get_redir(t_hell *hell, t_proc *proc, char *str)
{
	t_redir	*node;
	t_redir	*new;
	int		res;

	res = 0;
	new = create_redir(hell, proc, str, &res);

	if (!*(proc->redirs))
		*(proc->redirs) = new;
	else
	{
		node = *(proc->redirs);
		while (node->next)
			node = node->next;
		node->next = new;
	}
	return (res - 1);
}