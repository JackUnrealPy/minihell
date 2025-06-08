/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:52:33 by agara             #+#    #+#             */
/*   Updated: 2025/05/13 21:43:33 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int	get_quotelen(char *cmd)
{
	int	i;
	int	inquote;

	i = -1;
	inquote = 0;
	while (cmd[++i])
	{
		if (!inquote)
		{
			if (cmd[i] == '\"')
				inquote = 1;
			if (cmd[i] == '\'')
				inquote = 2;
			continue ;
		}
		if (inquote == 1 && cmd[i] == '\"')
			return (i);
		if (inquote == 2 && cmd[i] == '\'')
			return (i);
	}
	return (0);
}

void	purge_quotes(t_hell *hell, t_proc *proc, t_token **v)
{
	int		i;
	t_token	*token;

	(void)proc;
	token = *v;

	(void) hell;
	while (token)
	{
		i = -1;
		if (!((char *)token->token)[0] && *v == token)
		{
			pop_token(v, token->token, 0);
			token = *v;
			continue;
		}
		while (((char *)token->token)[++i])
		{
			if ((((char *)token->token)[i] == '\'' || ((char *)token->token)[i] == '\"') && !is_immun(token->expansion, i))
				i += ft_update_quote(hell, token, i) - 1;
		}
		token = token->next;
	}
}