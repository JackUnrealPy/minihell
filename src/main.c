/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:12:38 by agara             #+#    #+#             */
/*   Updated: 2025/06/07 21:28:47 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>

int g_sig_flag=0;

void handle_sig(int sig)
{
	(void)sig;

	g_sig_flag = 1;
	write(1, "\n", 1);

	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	// ioctl(STDOUT_FILENO, TIOCSTI, "\n");
}

int	all_whitespace(char *cmd)
{
	int i;
	int space;
	
	i = 0;
	space = 0;
	while (cmd && cmd[i])
	{
		if (!ft_isspace(cmd[i]))
			space++;
		i++;
	}
	if (space == 0)
		return 1;
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_hell	hell;

	(void)argc;
	(void)argv;
	
	init(&hell, envp);
	hell.cmd = NULL;
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
    while (1)
    {
		if (g_sig_flag == SIGINT)
		{

			hell.lastexit = 130;
			g_sig_flag = 0;
		}
		hell.cmd = readline("minishell> ");
		{
			if (!hell.cmd)
			{
				free(hell.cmd);
				write(1, "exit\n", 5);
				break;
			}
			if (!all_whitespace(hell.cmd))
			{
				add_history(hell.cmd);
				local_init(&hell, hell.cmd);
				parse(&hell, hell.cmd);
				// print_list(*(hell.head));
				if (!hell.syntaxerr)
					loop_cmds(&hell);
				hell.syntaxerr = 0;
				ft_terminate(1, &hell.cmd);
				close_proc(&hell);
			}
		}
		
    }
    rl_clear_history();
	throw_garbage(hell.freeme);
	ft_terminate(1, &(hell.head));
	return (hell.lastexit);
}
