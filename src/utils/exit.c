
#include "../../includes/minishell.h"

void	jump_ship(t_hell *hell, short int exitcode)
{
	t_proc  *proc;
	t_proc	*tmp;

	proc = *(hell->head);
	while (proc)
	{
		tmp = proc->next;
		throw_garbage(proc->freeme);
		ft_terminate(1, &proc);
		proc = tmp;
	}
	throw_garbage(hell->freeme);
	ft_terminate(1, &(hell->head));
	exit(exitcode);
}

void	sysntaxerr(t_hell *hell, char token)
{
	if (hell->syntaxerr)
		return ;
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putchar_fd(token, 2);
	ft_putstr_fd("\'\n", 2);
	hell->syntaxerr = 1;
	hell->lastexit = 2;
}