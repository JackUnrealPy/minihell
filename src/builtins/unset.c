#include "../../includes/minishell.h"

void	ft_unset(t_hell *hell, char **envp, char *var_to_delete)
{
	int	i;
	int	strcount;

	if (!var_to_delete)
		return ;
	if (hell->exec_error)
		return ;
	i = 0;
	strcount = 0;
	while (envp[strcount])
		strcount++;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_to_delete, ft_strlen(var_to_delete)) == 0)
		{
			while (envp[i])
			{
				envp[i] = envp[i + 1];
				i++;
			}
			envp[i] = NULL;
			break ;
		}
		i++;
	}
}
