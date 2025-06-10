/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:27:55 by agara             #+#    #+#             */
/*   Updated: 2025/06/10 14:19:25 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_redir	*create_redir(t_hell *hell, t_proc *proc, int type)
{
	t_redir	*node;
	t_redir	*new;

	new = ft_malloc(hell, proc->freeme, malloc(sizeof(t_redir)));
	new->type = type;
	new->redt = NULL;
	new->pathordel = NULL;
	new->next = NULL;
	if (!*(proc->redirs))
		*(proc->redirs) = new;
	else
	{
		node = *(proc->redirs);
		while (node->next)
			node = node->next;
		node->next = new;
	}
	return (new);
}

static int	check_red_type(char *type, t_token *token)
{
	int	res;
	int	i;

	res = -1;
	if (ismeta(type) == '<')
		res = 0;
	else if (ismeta(type) == '>')
		res = 1;
	else if (ismeta(type) == '+')
		res = 2;
	else if (ismeta(type) == '-')
		res = 4;
	if (!token && res != -1)
		return (-2);
	if (res != 4)
		return (res);
	i = -1;
	while (((char *)token->token)[++i])
	{
		if (((char *)token->token)[i] == '\''
			|| ((char *)token->token)[i] == '\"')
			return (3);
	}
	return (res);
}

int	gen_redir(t_hell *hell, t_proc *proc, t_redir *red, t_token **token)
{
	int		type;
	t_token	*tmp;

	tmp = (*token)->next;
	type = check_red_type((*token)->token, tmp);
	if (type == -2)
		sysntaxerr(hell, "newline", 7);
	if (type != -1)
	{
		if ((!tmp || ismeta(tmp->token)) && !(*token)->next)
			return (sysntaxerr(hell, (*token)->token,
					ft_strlen((*token)->token)), 0);
		else if ((!tmp || ismeta(tmp->token)) && (*token)->next->token)
			return (sysntaxerr(hell, (*token)->next->token,
					ft_strlen((*token)->token)), 0);
		pop_token(proc->tokens, (*token)->token, 0);
		red = create_redir(hell, proc, type);
		*token = tmp->next;
		red->redt = cut_token(proc->tokens, tmp);
	}
	else
		*token = tmp;
	return (1);
}
