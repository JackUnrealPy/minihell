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
	int		len;
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
		len = 0;
		if (cmd[j] == '\"')
		{
			len = get_quotelen(cmd + j);
		}
	}
	(void)len;
	printf("str:[%s]",cmd + i);
	return (res);
}

int	get_cmdarr(t_hell *hell, t_proc *proc, char **ptr, int i)
{
	int		len;
	char	*cmd;
	char	*cmds;
	char	**processed_cmds;

	processed_cmds = NULL;
	cmds = *ptr + i;
	cmd = NULL;
	len = 0;
	while (cmds[++len])
	{
		if (cmds[len] == '<' || cmds[len] == '>' || cmds[len] == '|')
			break;
		if (cmds[len] == '\'' || cmds[len] == '\"')
		{
			len += handle_quote(hell, proc, ptr ,i + len);
			cmds = *ptr + i;
			printf("cmdarr [%s]len[%d]\n", cmds, len);
		}
		else if (cmds[len] == '$')
		{
			printf("WHAAAT :[%s]\n", cmds + len);
			if (!ft_isalpha(cmds[len + 1]) && cmds[len +1] != '?')
				continue ;
			ft_expand(hell, proc, ptr, len + i);
			len = 0;
			cmds = *ptr + i;
		}
	}	
	len = 0;
	while (cmds[len] && (!ismeta(cmds + len) || (cmds[len] == '$')))
		len++;
	cmd = ft_malloc(hell, proc->freeme, ft_substr(cmds, 0, len));
	// if (ft_strlen(cmd) >= 7 && !ft_strncmp(cmd, "export", 6) && ft_isspace(cmd[6]))
	// 	processed_cmds = parse_export(hell, proc, cmd);
	// else
		processed_cmds = (char **)ft_mallocarr(hell, proc->freeme ,(void **)ft_split(cmd, "\n\t\v\f\r "));
	if (!(proc->cmd))
		proc->cmd = processed_cmds;
	else
		add_arr_to_cmdarr(hell, proc, processed_cmds);
	return (len - 1);
}



void	parse(t_hell *hell, char *cmd, t_proc *proc)
{
	int		i;
	
	i = -1;
	while (cmd[++i])
	{
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
		else if (cmd[i] == '\"'|| cmd[i] == '\'')
			handle_quote(hell, proc, &cmd , i--);
		else
			i += get_cmdarr(hell, proc, &cmd, i);
	}
}