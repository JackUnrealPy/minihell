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
	int		n;
	int		qflag;
	
	i = 0;
	j = 0;
	while (*str && ft_isspace(*str))
	{
		str++;
		j++;
	}
	if (*str == '<' || *str == '>')
		sysntaxerr(hell, *str);
	qflag = 0;
	while (str[i] && !ft_isspace(str[i]))
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (i == 0)
				qflag = 1;
			i += handle_quote(hell, proc, &str, i) + 1;
		}
		else if (str[i] == '$')
			i += ft_expand(hell, proc, &str, i);
		else if (str[i] == '|')
		{
			sysntaxerr(hell, *(str + i));
			break;
		}
		else
			i++;
	}
	new->pathordel = ft_malloc(hell, proc->freeme, ft_calloc(i + 1, sizeof(char)));
	new->next = NULL;
	n = 0;
	while (n <= i)
	{
		new->pathordel[n] = str[n];
		n++;
	}
	if (new->type == 3 && !qflag)
		new->type = 4;
	return (j + i + 3);
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