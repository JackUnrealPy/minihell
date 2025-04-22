/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:52:33 by agara             #+#    #+#             */
/*   Updated: 2025/04/22 21:03:02 by agara            ###   ########.fr       */
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

int	get_squote(t_hell *hell, t_proc *proc, char *quote)
{
	char	*str;
	int		len;
	int		i;

	len = 0;
	len = get_quotelen(quote);
	if (!len)
		sysntaxerr();
	str = NULL;
	str = ft_malloc(hell, proc->freeme, ft_calloc(sizeof(char) ,len + 1));
	i = -1;
	while (++i < len - 1)
		str[i] = quote[i + 1];
	if (!proc->cmd)
	{
		proc->cmd = ft_malloc(hell, proc->freeme, malloc(sizeof (char *) * 2));
		proc->cmd[0] = str;
		proc->cmd[1] = NULL;
	}
	else
		add_to_cmdarr(hell, proc, str);
	return (len);
}

int	get_dquote(t_hell *hell, t_proc *proc, char **cmd, int pos)
{
	char	*str;
	int		len;
	int		i;

	len = 0;
	len = get_quotelen(*cmd + pos);
	if (!len)
		sysntaxerr();
	str = NULL;
	i = 0;
	while (++i < len)
	{
		if ((*cmd)[pos + i] == '$')
		{
			ft_expand(hell, proc, cmd, pos + i);
			len = get_quotelen(*cmd + pos);
		}
	}
	str = ft_malloc(hell, proc->freeme, ft_substr(*cmd + 1, pos, len - 1));
	if (!proc->cmd)
		proc->cmd = (char **)ft_mallocarr(hell, proc->freeme ,(void **)ft_split(*cmd, "\n\t\v\f\r\" "));
	else
		add_to_cmdarr(hell, proc, str);
	return (len); 
}