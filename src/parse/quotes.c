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

int	handle_quote(t_hell *hell, t_proc *proc, char **cmd, int pos)
{
	char	*str;
	char	*res;
	int		len;

	res = NULL;
	len = 1;
	while (*(*cmd + len + pos) && *(*cmd + pos + len) != *(*cmd+pos))
		len++;
	len ++;
	str = NULL;
	if (*(*cmd+pos) == '\'')
	{
		str =  get_squote(hell, proc, *cmd + pos);
		res = ft_malloc(hell, proc->freeme, ft_calloc(sizeof(char) , ((ft_strlen(*cmd) - len) + ft_strlen(str) + 1)) );
		ft_memcpy(res, *cmd, pos);
		ft_memcpy(res + pos, str, ft_strlen(str));
		ft_memcpy(res + pos + ft_strlen(str), *cmd + pos + len, ft_strlen(*cmd + pos + len));
	}
	else
	{
		str = get_dquote(hell, proc, cmd , pos);
		res = ft_malloc(hell, proc->freeme, ft_calloc(sizeof(char) , ((ft_strlen(*cmd) - len) + ft_strlen(str) + 1)) );
		ft_memcpy(res, *cmd, pos);
		ft_memcpy(res + pos, str, ft_strlen(str));
		ft_memcpy(res + pos + ft_strlen(str), *cmd + pos + ft_strlen(str) + 2, ft_strlen(*cmd + pos + ft_strlen(str) + 2));
	}
	*cmd = res;
	return (ft_strlen(str) - 1);
	
}

char	*get_squote(t_hell *hell, t_proc *proc, char *quote)
{
	char	*str;
	int		i;
	int		len;
	
	len = 0;
	len = get_quotelen(quote);
	if (!len)
		sysntaxerr(hell, quote, 1);
	str = NULL;
	str = ft_malloc(hell, proc->freeme, ft_calloc(sizeof(char) ,len + 1));
	i = -1;
	while (++i < len - 1)
		str[i] = quote[i + 1];
	return (str);
}

char	*get_dquote(t_hell *hell, t_proc *proc, char **cmd, int pos)
{
	char	*str;
	int		len;
	int		i;

	len = 0;
	len = get_quotelen(*cmd + pos);
	if (!len)
		sysntaxerr(hell, *cmd + pos, 1);
	str = NULL;
	i = 0;
	while (++i < len)
	{
		if ((*cmd)[pos + i] == '$')
		{
			ft_expand(hell, proc, cmd, pos + i);
			len = get_quotelen(*cmd + pos);
			if (!len)
				sysntaxerr(hell, *cmd + pos, 1);
		}
	}
	str = ft_malloc(hell, proc->freeme, ft_substr(*cmd + 1, pos, len - 1));
	return (str); 
}