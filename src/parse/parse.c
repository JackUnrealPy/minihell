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


void	add_to_cmdarr(t_hell *hell, t_proc *proc, char *addme)
{
	int		len;
	char	**res;

	len = -1;
	if (!proc->cmd)
	{
		proc->cmd = ft_malloc(hell ,proc->freeme, malloc(sizeof(char *) * 2));
		proc->cmd[0] = addme;
		proc->cmd[1] = NULL;
		return ;
	}
	while (proc->cmd[++len])
		;
	res = ft_malloc(hell ,proc->freeme, malloc(sizeof(char *) * (len + 2)));
	len = -1;
	while (proc->cmd[++len])
		res[len] = proc->cmd[len];
	res[len++] = addme;
	res[len] = NULL;
	proc->cmd = res;
}


int	pipecommandcheck(t_proc **head)
{
	t_proc	*node;

	if (!*head)
		return (-1);
	node = *head;
	while (node->next)
		node = node->next;
	if (node->cmd)
		return 1;
	return 0;
}

void	handlepipe(t_hell *hell, char *cmd, int i, t_proc *proc)
{
	t_proc	*next;
	
	next = NULL;
	if (!pipecommandcheck(hell->head))
		return (sysntaxerr(hell, cmd + i, 1));
	if (cmd[i + 1])
		next = create_proc(hell);
	addproc(hell->head ,next);
	parse(hell, ft_malloc(hell, next->freeme, ft_strdup(cmd + i + 1)), proc->next);
}

void	add_arr_to_cmdarr(t_hell *hell, t_proc *proc, char **addme)
{
	int		lendest;
	int		lensrc;
	char	**res;

	lensrc = -1;
	while (proc->cmd[++lensrc])
		;
	lendest = -1;
	while (addme[++lendest])
		;
	res = ft_malloc(hell ,proc->freeme, malloc(sizeof(char *) * (lendest  + lensrc + 1)));
	lensrc = -1;
	while (proc->cmd[++lensrc])
		res[lensrc] = proc->cmd[lensrc];
	lendest = -1;
	while (addme[++lendest])
		res[lensrc + lendest] = addme[lendest];
	res[lendest + lensrc] = NULL;
	proc->cmd = res;
}

char **parse_export(t_hell *hell, t_proc *proc, char* cmd)
{
	int		i;
	int		j;
	char	**res;

	res = NULL;
	res = ft_malloc(hell, proc->freeme, malloc(sizeof(char *) * 3));
	res[0] = ft_malloc(hell, proc->freeme, ft_strdup("export"));
	i = 5;
	while (cmd[++i])
	{
		if (!ft_isspace(cmd[i]))	
			break;
	}
	j = i;
	while (cmd[j])
	{
		if (cmd[j] == '\"' || cmd[j] == '\'')
			j += handle_quote(hell, proc, &cmd, j);
		else
			j++;
	}
	res[1] = ft_malloc(hell, proc->freeme, ft_strdup(cmd + i));
	return (res);
}

int	get_cmdarr(t_hell *hell, t_proc *proc, char **ptr, int i)
{
	int		len;
	char	*cmds;
	int		lasttoken;
	int		inspace;

	lasttoken = 0;
	inspace = 0;
	cmds = *ptr + i;
	len = -1;
	while (cmds[++len])
	{
		if (ft_isspace(cmds[len]) && !inspace)
		{
			add_to_cmdarr(hell, proc, ft_malloc(hell, proc->freeme, ft_substr(cmds, lasttoken, len - lasttoken)));
			inspace = 1;
		}
		if (!ft_isspace(cmds[len]) && inspace)
		{
			inspace = 0;
			lasttoken = len;
		}	
		if (cmds[len] == '$')
		{
			if (!ft_isalpha(cmds[len + 1]) && cmds[len +1] != '?')
				continue ;
			len += ft_expand(hell, proc, ptr, len + i) - 1;
			cmds = *ptr + i;
		}
		else if (cmds[len] == '<' || cmds[len] == '>' || cmds[len] == '|')
			break;
		if (cmds[len] == '\'' || cmds[len] == '\"')
		{
			len += handle_quote(hell, proc, ptr ,i + len);
			cmds = *ptr + i;
		}
	}
	if ((!cmds[len] || !inspace) && (len - lasttoken) > 0)
		add_to_cmdarr(hell, proc, ft_malloc(hell, proc->freeme, ft_substr(cmds, lasttoken, len - lasttoken)));
	// if (ft_strlen(cmd) >= 7 && !ft_strncmp(cmd, "export", 6) && ft_isspace(cmd[6]))
	// 	processed_cmds = parse_export(hell, proc, cmd);
	return (len - 1);
}



void	parse(t_hell *hell, char *cmd, t_proc *proc)
{
	int		i;
	
	i = -1;
	while (cmd[++i])
	{
		if (hell->syntaxerr)
			return ;
		if (cmd[i] == '$')
			ft_expand(hell, proc, &cmd, i);
		if (ft_isspace(cmd[i]))
			continue ;
		else if (cmd[i] == '|')
		{
			handlepipe(hell, cmd, i, proc);
			break ;
		}
		else if (cmd[i] == '>' || cmd[i] == '<')
			i += get_redir(hell, proc, cmd + i);
		else
			i += get_cmdarr(hell, proc, &cmd, i);
	}
}