/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:12:38 by agara             #+#    #+#             */
/*   Updated: 2025/03/22 21:28:09 by agara            ###   ########.fr       */
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
	while (++i < 2)
	{
		writeprompt();
		cmd = get_next_line(0, &flag);
		local_init(&hell, cmd);
		parse(&hell, cmd);
		ft_terminate(1, &cmd);
		close_proc(&hell);
		
	}
	throw_garbage(hell.freeme);
	ft_terminate(1, &(hell.head));
	return (0);
}
