/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:12:38 by agara             #+#    #+#             */
/*   Updated: 2025/03/04 20:15:34 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	int		flag;
	t_hell	hell;

	flag = 0;
	(void)argc;
	(void)argv;
	init(&hell, envp);
	while (1)
	{
		writeprompt();
		cmd = get_next_line(0, &flag);
		if (!flag)
		{
			flag = -1;
			get_next_line(0, &flag);
			jumpship(hell);
		}
		parse(cmd);
		printf("%s",cmd);
	}
	return (0);
}
