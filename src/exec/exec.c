#include "../../includes/minishell.h"

int	loop_cmds(t_hell *hell, char **cmd)
{
	if ((*hell->head) && !(*hell->head)->next)
		single_cmd(hell, (*hell->head), cmd);
	else if ((*hell->head) && (*hell->head)->next)
		ft_pipex(hell, cmd);
	return (0);
}