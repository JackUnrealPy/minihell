/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:52:33 by agara             #+#    #+#             */
/*   Updated: 2025/06/07 18:42:04 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_expand(t_hell *hell, t_proc *proc, t_token *token, int pos)
{
	int		i;
	char	*var;

	var = get_exp(hell, proc, (char *)token->token + pos, &i);
	add_num(hell, &(token->expansion), i);
	return (var);
}

static int	check_qlen(t_hell *hell, char *token, int i)
{
	int	end;

	end = 0;
	end = get_quotelen(token + i);
	if (!end)
		sysntaxerr(hell, token, ft_strlen(token));
	return (end);
}

static void	step_over_q(t_hell *hell, t_token *token, int *i, int *qi)
{
	int	end;

	if (*qi != -1)
	{
		end = get_quotelen((char *)token->token + *qi);
		if ((end + *qi) < *i)
			*qi = -1;
	}
	if (*(char *)(token->token) && ((char *)token->token)[*i] == '\"'
		&& *qi == -1)
	{
		check_qlen(hell, (char *)token->token, *i);
		*qi = *i;
	}
	else if (*(char *)(token->token) && ((char *)token->token)[*i] == '\''
		&& *qi == -1)
	{
		end = check_qlen(hell, (char *)token->token, *i);
		(*i) += end;
	}
}

void	parse_expand(t_hell *hell, t_proc *proc, t_token **tokens)
{
	t_token	*token;
	int		i;
	char	*val;
	int		qi;

	token = *tokens;
	while (token)
	{
		i = -1;
		qi = -1;
		while (((char *)token->token)[++i])
		{
			if (((char *)token->token)[i] == '$')
			{
				add_num(hell, &(token->expansion), i);
				val = ft_expand(hell, proc, token, i);
				ft_update_token(hell, token, i, val);
				i += ft_strlen(val) - 1;
				pop_free(proc->freeme, val);
			}
			else
				step_over_q(hell, token, &i, &qi);
		}
		token = token->next;
	}
}
