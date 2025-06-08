/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:52:33 by agara             #+#    #+#             */
/*   Updated: 2025/06/08 16:53:15 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

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

void	parse_redirs(t_hell *hell, t_proc *proc, t_token **v)
{
	t_redir	*node;
	char	*backup;
	
	(void)v;
	collect_redirs(hell, proc);
	node = *(proc->redirs);
	while (node)
	{
		backup = ft_strdup((char *)node->redt->token);
		if (!backup)
			jump_ship(hell, 1);
		if (node->type != 4 && node->type != 3)
			parse_expand(hell, proc, &node->redt);
		if (!((char *)node->redt->token)[0])
		{
			ft_terminate(1, &node->redt->token);
			node->redt->token = backup;
		}
		else
			ft_terminate(1, &backup);
		purge_quotes(hell, proc, &node->redt);
		node->pathordel = ft_malloc(hell, proc->freeme, ft_strdup((char *)node->redt->token));
		node = node->next;
	}
	node = *(proc->redirs);
	while (node)
	{
		if (node->redt)
			del_token(&node->redt, node->redt);
		node = node->next;
	}
}

int	check_red_type(char *type, t_token *token)
{
	int	res;
	int	i;

	res = -1;
	if(ismeta(type) == '<')
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
		if (((char *)token->token)[i] == '\'' || ((char *)token->token)[i] == '\"')
			return (3);
	}
	return (res);
}

void	collect_redirs(t_hell *hell, t_proc *proc)
{
	t_token	*token;
	t_token	*tmp;
	t_redir	*red;
	int		type;

	token = *(proc->tokens);
	while (token)
	{
		tmp = token->next;
		type = check_red_type(token->token, tmp);
		if (type == -2)
			sysntaxerr(hell, (char *)token->token, ft_strlen((char *)token->token));
		if (type != -1)
		{
			if ((!tmp || ismeta(tmp->token)) && !token->next)
				return (sysntaxerr(hell, token->token, ft_strlen(token->token)));
			else if ((!tmp || ismeta(tmp->token)) && token->next->token)
				return (sysntaxerr(hell, token->next->token, ft_strlen(token->token)));
			pop_token(proc->tokens, token->token, 0);
			red = create_redir(hell, proc, type);
			token = tmp->next;
			red->redt = cut_token(proc->tokens,  tmp);
		}
		else
			token = tmp;
	}
}