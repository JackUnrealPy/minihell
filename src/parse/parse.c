/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:50:23 by agara             #+#    #+#             */
/*   Updated: 2025/03/04 20:05:03 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_quotelen(const char *cmd)
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
			return (i + 1);
		if (inquote == 2 && cmd[i] == '\'')
			return (i + 1);
	}
	return (0);
}

int	ismeta(const char *c)
{
	if (*c == '|' || *c == '\'' || *c == '\"' || *c == '$')
		return (*c);
	if (*c == '<')
	{
		if (*(c + 1) == '<')
			return ('-');
		return (*c);
	}
	if (*c == '>')
	{
		if (*(c + 1) == '>')
			return ('+');
		return (*c);
	}
	return (0);
}

void	sysntaxerr()
{
	perror("syntax error");
	exit(2);
}

char	*getquote(const char *cmd, int *index)
{
	char	*str;
	int		len;
	int		i;

	i = -1;
	len = 0;
	str = NULL;
	if (*cmd == '\'' || *cmd == '\"')
	{
		len = get_quotelen(cmd);
		if (!len)
			sysntaxerr();
		str = ft_calloc(sizeof(char) ,len);
		if (!str)
			exit(1);
		while (++i < len - 2)
			str[i] = cmd[i + 1];
	}
	*index += len;
	return (str);
}
void	addproc(t_proc *head, t_proc *next)
{
	t_proc	*node;

	node = head;
	while (node->next)
		node = node->next;
	next->prev = node;
	node->next = next;
}

void	parse(t_hell *hell, const char *cmd)
{
	int		i;
	int		ch;
	char	*unit;
	t_proc	*next;
	
	i = -1;
	unit = NULL;	
	while (cmd[++i])
	{
		ch = ismeta(cmd + i);
		if (ch)
		{
			if (ch == '|')
			{
				if (!i)
					sysntaxerr();
				next = create_proc((const char*)(cmd + i + 1));
				addproc(hell->head ,next);
				unit = ft_calloc(sizeof(char) , i + 1);
				if (!unit)
					exit(1);
				ft_strlcpy(unit, cmd, i + 1);
				parse(hell, cmd + i + 1);
				break ;
			
			}
			if (ch == '\'' || ch == '\"')
				char *str = getquote(cmd + i, &i);
		}
	}
	(void)hell;
}
