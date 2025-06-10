/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:43:29 by agara             #+#    #+#             */
/*   Updated: 2025/06/10 13:43:30 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_token(t_hell *hell, char *cmd)
{
	int	i;
	int	j;

	if (ismeta(cmd) == '+' || ismeta(cmd) == '-')
		return (add_token(hell, hell->tokens, ft_substr(cmd, 0, 2)), 1);
	else if (ismeta(cmd))
		return (add_token(hell, hell->tokens, ft_substr(cmd, 0, 1)), 0);
	i = -1;
	while (cmd[++i])
	{
		if (ismeta(cmd + i) || ft_isspace(cmd[i]))
			return (add_token(hell, hell->tokens, ft_substr(cmd, 0, i)), i - 1);
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			j = get_quotelen(cmd + i);
			if (!j)
				return (sysntaxerr(hell, cmd + i, 1), 0);
			i += j;
		}
	}
	if (!cmd[i] && i > 0)
		return (add_token(hell, hell->tokens, ft_substr(cmd, 0, i)), i - 1);
	return (i);
}

void	tokenize(t_hell *hell, char *cmd)
{
	int		i;

	hell->tokens = malloc(sizeof(t_token *));
	if (!hell->tokens)
		jump_ship(hell, 1);
	*(hell->tokens) = NULL;
	i = -1;
	while (cmd[++i])
	{
		if (!ft_isspace(cmd[i]))
			i += get_token(hell, cmd + i);
	}
}

static int	handle_pipe(t_hell *hell, t_proc *proc,
	t_token **node, t_token **tmp)
{
	if (!(*node)->next || !(*node)->prev
		|| ((char *)(*node)->next->token)[0] == '|')
		return (sysntaxerr(hell, "newline", 7), 0);
	if (*node == *(proc->tokens))
		return (sysntaxerr(hell, "|", 1), 0);
	*tmp = (*node)->prev;
	del_token(proc->tokens, *node);
	*node = (*tmp)->next;
	(*node)->prev = NULL;
	(*tmp)->next = NULL;
	proc = create_proc(hell);
	addproc(hell->head, proc);
	*(proc->tokens) = *node;
	return (1);
}

void	divide_procs(t_hell *hell, t_proc *proc)
{
	t_token	*node;
	t_token	*tmp;

	*(proc->tokens) = *(hell->tokens);
	*(hell->tokens) = NULL;
	tmp = NULL;
	node = *(proc->tokens);
	while (node)
	{
		if (((char *)node->token)[0] == '|')
		{
			if (!handle_pipe(hell, proc, &node, &tmp))
				return ;
		}
		else
		{
			tmp = node;
			node = node->next;
		}
	}
}
