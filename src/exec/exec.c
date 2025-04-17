#include "../../includes/minishell.h"

int	loop_cmds(t_hell *hell, char **cmd)
{
	if ((*hell->head) && !(*hell->head)->next
		&& !heredoc_check((*(*hell->head)->redirs)))
	{
		if (!determine_builtin(hell, (*hell->head), cmd, 0) && !hell->exec_error)
			single_cmd(hell, (*hell->head), cmd);
	}
	else if ((*hell->head) && !(*hell->head)->next
		&& heredoc_check((*(*hell->head)->redirs)))
		single_heredoc(hell, (*hell->head), (*(*hell->head)->redirs), cmd);
	else if ((*hell->head) && (*hell->head)->next)
		ft_pipex(hell, cmd);
	return (0);
}
