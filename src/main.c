/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:12:38 by agara             #+#    #+#             */
/*   Updated: 2025/03/19 20:54:16 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_procclear(t_proc **proc)
{
	void	*tempnext;

	if (!*proc)
		return ;
	while (*proc)
	{
		tempnext = (*proc)->next;
		ft_terminate(1, (*proc)->input);
		ft_terminate(1, proc);
		proc = tempnext;
	}
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
	while (1)
	{
		writeprompt();
		cmd = get_next_line(0, &flag);
		parse(&hell, cmd);
		ft_procclear(hell.head);
	}
	return (0);
}
