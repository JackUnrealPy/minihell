/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:12:38 by agara             #+#    #+#             */
/*   Updated: 2025/05/17 21:58:56 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int g_sig_flag=0;

void handle_sig(int sig)
{
	g_sig_flag = sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	t_hell	hell;

	(void)argc;
	(void)argv;
	cmd = NULL;
	init(&hell, envp);
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
    while (1)
    {
        cmd = readline("minishell> ");
		if (!cmd)
		{
			printf("exit\n");
			break;
		}
		if (g_sig_flag == SIGINT)
		{
			hell.lastexit = 130;
			g_sig_flag = 0;
		}
		add_history(cmd);
		local_init(&hell, cmd);
		parse(&hell, cmd, *(hell.head));
		// print_list(*(hell.head));
		if (!hell.syntaxerr)
		{
			loop_cmds(&hell);
		}
		hell.syntaxerr = 0;
		ft_terminate(1, &cmd);
		close_proc(&hell);
    }
    rl_clear_history();
	throw_garbage(hell.freeme);
	ft_terminate(1, &(hell.head));
	return (hell.lastexit);
}
