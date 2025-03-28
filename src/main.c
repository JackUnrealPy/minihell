/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:12:38 by agara             #+#    #+#             */
/*   Updated: 2025/03/28 17:28:29 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	while (1)
	{
		writeprompt();
		cmd = get_next_line(0, &flag);
		local_init(&hell, cmd);
		parse(&hell, cmd, *(hell.head));
		print_list(*(hell.head));
		ft_terminate(1, &cmd);
		close_proc(&hell);
		
	}
	throw_garbage(hell.freeme);
	ft_terminate(1, &(hell.head));
	return (0);
}
