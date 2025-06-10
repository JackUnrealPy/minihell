/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:35:18 by agara             #+#    #+#             */
/*   Updated: 2025/06/10 13:41:36 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	add_to_cmdarr(t_hell *hell, t_proc *proc, char *addme)
{
	int		len;
	char	**res;

	len = -1;
	if (!proc->cmd)
	{
		proc->cmd = ft_malloc(hell, proc->freeme, malloc(sizeof(char *) * 2));
		proc->cmd[0] = addme;
		proc->cmd[1] = NULL;
		return ;
	}
	while (proc->cmd[++len])
		;
	res = ft_malloc(hell, proc->freeme, malloc(sizeof(char *) * (len + 2)));
	len = -1;
	while (proc->cmd[++len])
		res[len] = proc->cmd[len];
	res[len++] = addme;
	res[len] = NULL;
	proc->cmd = res;
}

static void	parse_iter(t_hell *hell, t_proc *proc, int ctrl,
		void (*f)(t_hell *, t_proc *, t_token **))
{
	while (proc)
	{
		if (ctrl == 1)
			f(hell, proc, proc->tokens);
		else if (!ctrl)
			f(hell, proc, NULL);
		proc = proc->next;
	}
}

static void	get_cmds(t_hell *hell, t_proc *proc, t_token **v)
{
	t_token	*token;

	(void)v;
	token = *(proc->tokens);
	while (token)
	{
		add_to_cmdarr(hell, proc, ft_malloc(hell, proc->freeme,
				ft_strdup(((char *)token->token))));
		token = token->next;
	}
}

void	parse(t_hell *hell, char *cmd)
{
	tokenize(hell, cmd);
	divide_procs(hell, *(hell->head));
	if (hell->syntaxerr)
		return ;
	parse_iter(hell, *(hell->head), 0, parse_redirs);
	parse_iter(hell, *(hell->head), 1, parse_expand);
	parse_iter(hell, *(hell->head), 0, word_split);
	parse_iter(hell, *(hell->head), 1, purge_quotes);
	parse_iter(hell, *(hell->head), 0, get_cmds);
}
