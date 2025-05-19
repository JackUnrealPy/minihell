#include "../../includes/minishell.h"

int	loop_cmds(t_hell *hell)
{
	if ((*hell->head) && !(*hell->head)->next)
		single_cmd(hell, (*hell->head));
	else if ((*hell->head) && (*hell->head)->next)
		ft_pipex(hell);
	return (0);
}
