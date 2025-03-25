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
			return (i);
		if (inquote == 2 && cmd[i] == '\'')
			return (i);
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
	*index += len ;
	return (str);
}



// int	pipecommandcheck(t_proc **head)
// {
// 	t_proc	*node;

// 	if (!*head)
// 		return (-1);
// 	node = *head;
// 	while (node->next)
// 		node = node->next;
// 	if (node->input)
// 		return 1;
// 	return 0;
// }

void	handlepipe(t_hell *hell, char *cmd, int i, t_proc *proc)
{
	t_proc	*next;
	
	next = NULL;
	// if (!pipecommandcheck(hell->head))
	// 	sysntaxerr();
	if (cmd[i + 1])
		next = create_proc(hell);
	addproc(hell->head ,next);
	parse(hell, ft_malloc(hell, next->freeme, ft_strdup(cmd + i + 1)), proc->next);
}

int	get_cmdarr(t_hell *hell, char *cmds, t_proc *proc)
{
	int		len;
	char	*cmd;

	cmd = NULL;
	(void)hell;
	len = -1;
	while (cmds[++len] && !ismeta(cmds + len))
		;
	cmd = ft_malloc(hell, proc->freeme, ft_substr(cmds, 0, len));
	proc->cmd = (char **)ft_mallocarr(hell, proc->freeme ,(void **)ft_split(cmd, "\n\t\v\f\r "));
	return (len - 1);
}


void	parse(t_hell *hell, char *cmd, t_proc *proc)
{
	int		i;
	
	i = -1;
	while (cmd[++i])
	{
		if (!ft_strncmp(cmd, "exit",4))
		{
			ft_terminate(1, &cmd);
			jump_ship(hell, 0);
		}
		if (ft_isspace(cmd[i]))
			continue ;
		else if (cmd[i] == '$')
			i += get_expandlen(cmd + i);
		else if (cmd[i] == '|')
		{
			handlepipe(hell, cmd, i, proc);
			break ;
		}
		else if (cmd[i] == '\'' || cmd[i] == '\"')
			i += get_quotelen(cmd + i);
		else
		{
			i += get_cmdarr(hell, cmd + i, proc);
		}
	}
}
