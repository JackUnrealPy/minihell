/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:52:33 by agara             #+#    #+#             */
/*   Updated: 2025/03/28 17:53:44 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

static int	get_quotelen(char *cmd)
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