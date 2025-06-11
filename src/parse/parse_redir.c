/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:52:33 by agara             #+#    #+#             */
/*   Updated: 2025/06/11 16:55:19 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	exp_hasspace(char *str)
{
	int	i;
	
	i = -1;
	while (str[++i])
	{
		if (!ft_isspace(str[i]))
			break ;
	}
	if (!str[i])
		return (0);
	i++;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	if (!str[i])
		return (0);
	return (1);
}

static void	process_redir(t_hell *hell, t_proc *proc, t_redir **node)
{
	char	*backup;

	if (proc->redirerr)
	{
		ft_terminate(1, &(*node)->redt->token);
		*node = (*node)->next;
		return ;
	}
	backup = ft_strdup((char *)(*node)->redt->token);
	if (!backup)
		jump_ship(hell, 1);
	if ((*node)->type != 4 && (*node)->type != 3)
		parse_expand(hell, proc, &(*node)->redt);
	if (!((char *)(*node)->redt->token)[0] || exp_hasspace((char *)(*node)->redt->token))
	{
		proc->redirerr = 1;
		ft_terminate(1, &(*node)->redt->token);
		(*node)->redt->token = backup;
	}
	else
		ft_terminate(1, &backup);
	purge_quotes(hell, proc, &(*node)->redt);
	(*node)->pathordel = ft_malloc(hell, proc->freeme,
			ft_strdup((char *)(*node)->redt->token));
	*node = (*node)->next;
}

static void	collect_redirs(t_hell *hell, t_proc *proc)
{
	t_token	*token;
	t_redir	*red;

	token = *(proc->tokens);
	while (token)
	{
		red = NULL;
		if (!gen_redir(hell, proc, red, &token))
			return ;
	}
}

void	parse_redirs(t_hell *hell, t_proc *proc, t_token **v)
{
	t_redir	*node;

	(void)v;
	collect_redirs(hell, proc);
	node = *(proc->redirs);
	while (node)
		process_redir(hell, proc, &node);
	node = *(proc->redirs);
	while (node)
	{
		if (node->redt)
			del_token(&node->redt, node->redt);
		node = node->next;
	}
}
