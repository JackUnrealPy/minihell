/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:42:36 by agara             #+#    #+#             */
/*   Updated: 2025/06/12 17:27:06 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_expansion(t_token *token, int num)
{
	int		i;

	i = 0;
	while (token->expansion[i] != -1)
		i++;
	if (num < 0)
	{
		num = -1;
		if (i > 1)
			token->expansion[i - 2] = num;
	}
	if (i > 0)
		token->expansion[i - 1] = num;
}

void	ft_update_token(t_hell *hell, t_token *token, int pos, char *str)
{
	int		len;
	char	*res;
	char	*val;

	val = token->token;
	len = ft_strlen(val) - get_last_num(token->expansion) + ft_strlen(str);
	res = ft_calloc(sizeof (char), len + 1);
	if (!res)
		jump_ship(hell, 1);
	ft_memcpy(res, val, pos);
	ft_memcpy(res + pos, str, ft_strlen(str));
	ft_memcpy(res + pos + ft_strlen(str),
		val + pos + get_last_num(token->expansion),
		ft_strlen(val) - pos - get_last_num(token->expansion));
	ft_terminate(1, &val);
	token->token = res;
	update_expansion(token, ft_strlen(str) - pos - 1);
}

static void	trim_token(t_token *token)
{
	int		i;
	int		j;

	i = 0;
	while (ft_isspace(((char *)token->token)[i]))
		i++;
	if (i)
		ft_memmove(token->token, token->token + i,
			ft_strlen((char *)token->token) - i + 1);
	j = -1;
	while (token->expansion && token->expansion[++j] != -1)
	{
		token->expansion[j] -= i;
		if (token->expansion[j] < 0)
			token->expansion[j] = 0;
	}
	i = ft_strlen((char *)token->token);
	if (!i)
		return ;
	while (ft_isspace(((char *)token->token)[i - 1]))
		i--;
	((char *)token->token)[i] = 0;
}

static int	split_w(t_hell *hell, t_token *token, int i)
{
	int	j;

	j = 0;
	while (ft_isspace(((char *)token->token)[i + j]))
		j++;
	if (j && !ft_isspace(((char *)token->token)[i + j]))
	{
		divide_tokens(hell, token, i, j);
		return (-1);
	}
	if ((((char *)token->token)[i] == '\''
		|| ((char *)token->token)[i] == '\"')
		&& !is_immun(token->expansion, i))
		return (get_quotelen((char *)token->token + i));
	return (0);
}

void	word_split(t_hell *hell, t_proc *proc, t_token **v)
{
	int		j;
	int		i;
	t_token	*token;

	(void)v;
	token = *(proc->tokens);
	while (token)
	{
		trim_token(token);
		i = -1;
		while (((char *)token->token)[++i])
		{
			j = 0;
			j = split_w(hell, token, i);
			if (j == -1)
				break ;
			i += j;
		}
		token = token->next;
	}
}
