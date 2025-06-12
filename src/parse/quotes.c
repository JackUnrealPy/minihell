/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:52:33 by agara             #+#    #+#             */
/*   Updated: 2025/06/12 17:27:33 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

	(void) proc;
	(void) hell;
	token = *v;
	while (token)
	{
		i = -1;
		if (!((char *)token->token)[0] && *v == token)
		{
			pop_token(v, token->token, 0);
			token = *v;
			continue ;
		}
		while (((char *)token->token)[++i])
		{
			if ((((char *)token->token)[i] == '\''
				|| ((char *)token->token)[i] == '\"')
				&& !is_immun(token->expansion, i))
				i += ft_update_quote(hell, token, i) - 1;
		}
		token = token->next;
	}
}

int	ft_update_quote(t_hell *hell, t_token *token, int pos)
{
	int		len;
	int		third;
	int		i;

	len = get_quotelen((char *)token->token + pos);
	if (!len--)
		return (sysntaxerr(hell, (char *)token->token + pos, 1), 0);
	third = ft_strlen((char *)token->token) - len - pos - 1;
	ft_memmove(token->token + pos, token->token + pos + 1, len);
	ft_memmove(token->token + pos + len, token->token + pos + len + 2, third);
	((char *)token->token)[len + pos + third] = 0;
	i = 0;
	while (token->expansion[i] != -1)
	{
		token->expansion[i] -= 2;
		if (token->expansion[i] < 0)
			token->expansion[i] = 0;
		i++;
	}
	return (len);
}
