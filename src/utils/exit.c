#include "../../includes/minishell.h"

void	jump_ship(t_hell *hell, short int exitcode)
{
	close_proc(hell);
	pop_token(hell->tokens, NULL, 1);
	throw_garbage(hell->freeme);
	ft_terminate(1, &(hell->head));
	if (hell->cmd)
		free(hell->cmd);
	exit(exitcode);
}

void	sysntaxerr(t_hell *hell, char *token, int len)
{
	int	i;

	if (hell->syntaxerr)
		return ;
	ft_putstr_fd("syntax error near unexpected token `", 2);
	i = 0;
	while (i < len)
	{
		ft_putchar_fd(*(token + i), 2);
		i++;
	}
	ft_putstr_fd("\'\n", 2);
	hell->syntaxerr = 1;
	hell->lastexit = 2;
}
