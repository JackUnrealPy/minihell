/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:52:33 by agara             #+#    #+#             */
/*   Updated: 2025/05/13 21:53:26 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*lookup_exp_val(t_hell *hell, t_proc *proc, char *str)
{
	char	*res;
	int		i;

	res = NULL;
	i = -1;
	while (hell->envp[++i])
	{
		if (!ft_strncmp(hell->envp[i], str, ft_strlen(str)) && hell->envp[i][ft_strlen(str)] == '=')
			res = ft_malloc(hell, proc->freeme, ft_substr(hell->envp[i], ft_strlen(str) + 1, ft_strlen(hell->envp[i]) - ft_strlen(str)));
	}

	return (res);
}

static char	*expand_exit(t_hell *hell, t_proc *proc)
{
	char	*var;

	var = NULL;
	var = ft_malloc(hell, proc->freeme, ft_itoa(hell->lastexit));
	return	(var);
}

char *get_var(t_hell *hell, t_proc *proc, char *str, int *i)
{
	char	*s;
	char	*var;

	while (++*i)
	{
		if(!str[*i] || !ft_isalnum(str[*i]))
		{
			s = ft_malloc(hell, proc->freeme, ft_substr(str, 1, *i - 1));
			var = lookup_exp_val(hell, proc, s);
			if (!var)
				var = getenv(s);
			break;	
		}
	}
	return (var);
}

char	*get_exp(t_hell *hell, t_proc *proc, char *str, int *i)
{
	char	*var;

	var = NULL;
	*i = 0;
	if (str[1] == '?')
	{
		var = expand_exit(hell, proc);
		*i = 2;
	}
	else
		var = get_var(hell, proc, str, i);
	if (*i == 1 && *str == '$')
		var = ft_malloc(hell, proc->freeme, ft_strdup("$"));	
	if (!var)
		var = ft_malloc(hell, proc->freeme, ft_strdup(""));
	return (var);
}

static char	*ft_expand(t_hell *hell, t_proc *proc, t_token *token, int pos)
{
	int		i;
	char	*var;

	var = get_exp(hell, proc, (char *)token->token + pos, &i);
	add_num(hell, &(token->expansion), i);
	return (var);
}

static int	step_over_q(t_token *token, int *i, int inquote)
{
	if (*(char*)(token->token) && ((char *)token->token)[*i] == '\"')
		inquote = *i + get_quotelen((char *)token->token + *i);
	else if (*(char*)(token->token) && ((char *)token->token)[*i] == '\'' && inquote < 1)
		*i += get_quotelen((char *)token->token + *i);
	return (inquote - 1);
}

void	parse_expand(t_hell *hell, t_proc *proc, t_token **tokens)
{
	t_token	*token;
	int		i;
	char	*val;
	int		inquote;

	token = *tokens;
	while (token)
	{
		i = -1;
		inquote = 0;
		while(((char *)token->token)[++i])
		{
			if (((char *)token->token)[i] == '$')
			{
				add_num(hell, &(token->expansion), i);	
				val = ft_expand(hell, proc, token, i);
				ft_update_token(hell, token, i, val);
				i += ft_strlen(val) - 1;
				inquote -= ft_strlen(val) - 1;
				pop_free(proc->freeme, val);
			}
			inquote = step_over_q(token, &i, inquote);
		}
		token = token->next;
	}
}
