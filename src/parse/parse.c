/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:50:23 by agara             #+#    #+#             */
/*   Updated: 2025/03/19 19:41:36agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ismeta(char *c)
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

int	get_expandlen(char *str)
{
	int	i;

	i = -1;
	while (!ft_isspace(str[++i]));
	return (i);
}

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
			return (i + 1);
		if (inquote == 2 && cmd[i] == '\'')
			return (i + 1);
	}
	return (0);
}

char	*getquote(char *cmd, int *index)
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

void	addproc(t_proc **head, t_proc *next)
{
	t_proc	*node;

	node = *head;
	while (node->next)
		node = node->next;
	next->prev = node;
	node->next = next;
}

int	pipecommandcheck(t_proc **head)
{
	t_proc	*node;

	if (!*head)
		return (-1);
	node = *head;
	while (node->next)
		node = node->next;
	if (node->input)
		return 1;
	return 0;
}

void	handlepipe(t_hell *hell, char *cmd, int i)
{
	t_proc	*next;
	
	next = NULL;
	if (!pipecommandcheck(hell->head))
		sysntaxerr();
	if (cmd[i + 1])
		next = create_proc((char*)(cmd + i + 1));
	addproc(hell->head ,next);
	parse(hell, ft_strdup(cmd + i + 1));
}


void	parse(t_hell *hell, char *cmd)
{
	int		i;
	
	i = -1;
	while (cmd[++i])
	{
		if (ft_isspace(cmd[i]))
			continue ;
		if (cmd[i] == '$')
			i += get_expandlen(cmd + i);
		if (cmd[i] == '|')
		{
			handlepipe(hell, cmd, i);
			break ;
		}
		if (cmd[i] == '\'' || cmd[i] == '\"')
			i += get_quotelen(cmd + i);
	}
	ft_terminate(1, &cmd);
}
