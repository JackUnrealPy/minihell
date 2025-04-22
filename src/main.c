/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:12:38 by agara             #+#    #+#             */
/*   Updated: 2025/04/22 21:08:07 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	t_hell	hell;

	(void)argc;
	(void)argv;
	cmd = NULL;
	init(&hell, envp);
    while (1)
    {
        cmd = readline("minishell> ");
        add_history(cmd);
		local_init(&hell, cmd);
		parse(&hell, cmd, *(hell.head));
		// print_list(*(hell.head));
		loop_cmds(&hell, &cmd);
		ft_terminate(1, &cmd);
		close_proc(&hell);
    }
    rl_clear_history();
	throw_garbage(hell.freeme);
	ft_terminate(1, &(hell.head));
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*cmd;
// 	t_hell	hell;
// 	int		flag;

// 	(void)argc;
// 	(void)argv;
// 	flag = 0;
// 	cmd = NULL;
// 	init(&hell, envp);
// 	int i = 0;
// 	while (i < 4)
// 	{
// 		writeprompt();
// 		cmd = get_next_line(0, &flag);
// 		local_init(&hell, cmd);
// 		parse(&hell, cmd, *(hell.head));
// 		//print_list(*(hell.head));
// 		loop_cmds(&hell, &cmd);
// 		ft_terminate(1, &cmd);
// 		close_proc(&hell);
// 		i++;
// 	}
// 	throw_garbage(hell.freeme);
// 	ft_terminate(1, &(hell.head));
// 	return (hell.lastexit);
// }

