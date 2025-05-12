#include "../../includes/minishell.h"

void print_list(t_proc *a)
{
	t_redir	*reds;
	int		i;

	while (a)
	{
		if (a->cmd && *(a->cmd))
		{
			i = -1;
			while (a->cmd[++i])
				printf("cmd [%d]:{%s}\n", i, a->cmd[i]);
		}
		reds = *(a->redirs);
		while (reds)
		{
			printf("reds [%d]:{%s}\n", reds->type, reds->pathordel);
			reds = reds->next;
		}	
		a = a->next;
	}
}