/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:12:38 by agara             #+#    #+#             */
/*   Updated: 2025/03/20 20:46:05 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_procclear(t_proc **proc)
{
	t_proc	*tempnext;
	t_proc	*node;

	if (!proc || !*proc)
		return ;
	node = *proc;
	while (node)
	{
		tempnext = node->next;
		ft_terminate(1, &(node->input));
		ft_terminate(1, &node);
		node = tempnext;
	}
}

void	local_init(t_hell *hell, char *cmd)
{
	t_proc	*proc;

	proc = create_proc(cmd);
	*(hell->head) = proc;
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	t_hell	hell;
	int		flag;

	(void)argc;
	(void)argv;
	flag = 0;
	cmd = NULL;
	init(&hell, envp);
	int i = -1;
	while (++i < 2)
	{
		writeprompt();
		cmd = get_next_line(0, &flag);
		local_init(&hell, cmd);
		parse(&hell, cmd);
		ft_procclear(hell.head);
	}
	
	ft_terminate(1, &(hell.head));
	return (0);
}
